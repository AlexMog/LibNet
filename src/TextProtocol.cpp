//
// LineProtocol.cpp for LineProtocol in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Apr 20 02:40:36 2015 Moghrabi Alexandre
// Last update Tue May  5 13:07:10 2015 Moghrabi Alexandre
//

#include <cstring>
#include <iostream>
#include "mognetwork/TcpASIOServer.hh"
#include "mognetwork/TcpASIOListener.hh"
#include "mognetwork/TextProtocol.hh"

namespace mognetwork
{
  namespace protocol
  {
    TextProtocol::TextProtocol(TcpSocket* socket, char* separator) :
      AProtocolListener(socket), m_fullDatas(NULL), m_separator(separator) {}

    TextProtocol::~TextProtocol() {}

    void TextProtocol::flushReader()
    {
      m_pendingDatas = TcpSocket::ReadedDatas();
      if (m_fullDatas != NULL)
	delete m_fullDatas;
      m_fullDatas = NULL;
    }

    TcpSocket::ReadedDatas& TextProtocol::getReadedDatas()
    {
      return *m_fullDatas;
    }

    Socket::Status TextProtocol::onReadTrigger()
    {
      std::size_t readed;
      char buffer[1024];
      
      Socket::Status status = m_socket->receive(buffer, 1023, readed, 0);
      if (status != Socket::Ok)
	return status;
      buffer[readed++] = 0;
      m_pendingDatas.datas.resize(m_pendingDatas.datas.size() + readed);
      std::strcat(&m_pendingDatas.datas[0], buffer);
      char* l;
      while ((l = std::strstr(&m_pendingDatas.datas[0], "\n")) != NULL)
	{
	  int size = l - &m_pendingDatas.datas[0];
	  if (size == 0)
	    {
	      m_pendingDatas.datas.clear();
	      break;
	    }
	  m_fullDatas = new TcpSocket::ReadedDatas();
	  m_fullDatas->datas.resize(l - &m_pendingDatas.datas[0] + 2);
	  std::memcpy(&m_fullDatas->datas[0],
		      &m_pendingDatas.datas[0],
		      l - &m_pendingDatas.datas[0]);
	  m_fullDatas->datas[m_fullDatas->datas.size() - 1] = 0;
	  if (m_pendingDatas.datas.size() != size + 2)
	    for (int i = 0; i < size + 1; ++i)
	      m_pendingDatas.datas.erase(m_pendingDatas.datas.begin());
	  m_socket->setAllDataReaded(m_fullDatas);
	  for (std::list<ITcpASIOListenerHandler*>::iterator it = m_socket->getServer()->getServerListener()->getListeners().begin();
	       it != m_socket->getServer()->getServerListener()->getListeners().end();
	       ++it)
	    (*it)->onReceivedData(*m_socket);
	  m_fullDatas = NULL;
	}
      return Socket::Waiting;
    }

    bool TextProtocol::datasFullyReceived()
    {
      return m_fullDatas != NULL
	&& m_fullDatas->datas.size() > 0
	&& std::strstr(&m_fullDatas->datas[0], "\n") != NULL;
    }

    void TextProtocol::onSendDatas(const char* data, std::size_t size, TcpSocket::Data& dataToSend)
    {
      dataToSend.resize(size + 1);
      std::memcpy(&dataToSend.front(), data, size);
      std::memcpy(&dataToSend.front() + size, "\n", 1);
    }

    Socket::Status TextProtocol::onReadAllTrigger(TcpSocket::Data& data)
    {
      bool received = false;

      while (!received)
	{
	  std::size_t readed;
	  char buffer[1024];
	  
	  Socket::Status status = m_socket->receive(buffer, 1023, readed, 0);
	  if (status != Socket::Ok)
	    return status;
	  buffer[readed++] = 0;
	  m_pendingDatas.datas.resize(m_pendingDatas.datas.size() + readed);
	  std::strcat(&m_pendingDatas.datas[0], buffer);
	  char* l;
	  if ((l = std::strstr(&m_pendingDatas.datas[0], "\n")) != NULL)
	    {
	      int size = l - &m_pendingDatas.datas[0];
	      if (size == 0)
		{
		  m_pendingDatas.datas.clear();
		  break;
		}
	      
	      data.resize(l - &m_pendingDatas.datas[0] + 2);
	      std::memcpy(&data[0],
			  &m_pendingDatas.datas[0],
			  l - &m_pendingDatas.datas[0]);
	      data[data.size() - 1] = 0;
	      if (m_pendingDatas.datas.size() != size + 2)
		for (int i = 0; i < size + 1; ++i)
		  m_pendingDatas.datas.erase(m_pendingDatas.datas.begin());
	      received = true;
	    }
	}
      return Socket::Ok;
    }
  }
}
