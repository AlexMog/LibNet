//
// LineProtocol.cpp for LineProtocol in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Apr 20 02:40:36 2015 Moghrabi Alexandre
// Last update Mon Apr 20 06:17:02 2015 Moghrabi Alexandre
//

#include <cstring>
#include <iostream>
#include "mognetwork/TcpASIOServer.hh"
#include "mognetwork/TcpASIOListener.hh"
#include "mognetwork/LineProtocol.hh"

namespace mognetwork
{
  namespace protocol
  {
    Socket::Status LineProtocol::onReadTrigger()
    {
      std::size_t readed;
      char buffer[1024];
      
      Socket::Status status = m_socket->receive(buffer, 1023, readed, 0);
      if (status != Socket::Ok)
	return status;
      buffer[readed++] = 0;
      m_pendingDatas.datas.resize(m_pendingDatas.datas.size() + readed);
      //      char* begin = &m_pendingDatas.datas[0] + m_pendingDatas.datas.size() - readed;
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
	  for (std::list<ITcpASIOListenerHandler*>::iterator it = m_socket->getServer()->getServerListener()->getListeners().begin(); it != m_socket->getServer()->getServerListener()->getListeners().end(); ++it)
	    (*it)->onReceivedData(*m_socket);
	  m_fullDatas = NULL;
	}
      return Socket::Waiting;
    }

    bool LineProtocol::datasFullyReceived()
    {
      return m_fullDatas != NULL
	&& m_fullDatas->datas.size() > 0
	&& std::strstr(&m_fullDatas->datas[0], "\n") != NULL;
    }

    void LineProtocol::onSendDatas(const char* data, std::size_t size, TcpSocket::Data& dataToSend)
    {
      dataToSend.resize(size + 1);
      std::memcpy(&dataToSend.front(), data, size);
      std::memcpy(&dataToSend.front() + size, "\n", 1);
    }

    Socket::Status LineProtocol::onReadAllTrigger(TcpSocket::Data& data)
    {
      /*      std::size_t readed;
      char buffer[1024];
      char* l;
      std::vector<char> _readed;
      
      while ((l = std::strstr(&m_pendingDatas.datas[0], "\n")) == NULL)
	{
	  Socket::Status status = m_socket->receive(buffer, 1024, readed, 0);
	  if (status != Socket::Ok)
	    return status;
	  _readed.resize(_readed.size() + readed);
	  char* begin = &_readed[0] + _readed.size() - readed;
	  std::memcpy(begin, buffer, readed);
	}
      if (l != NULL)
	{
	  size_t tmp = m_fullDatas.datas.size();
	  m_fullDatas.datas.resize(m_fullDatas.datas.size() +
				   l - &m_pendingDatas.datas[0] + 2);
	  std::memcpy(&m_fullDatas.datas[0] + tmp,
		      &m_pendingDatas.datas[0],
		      l - &m_pendingDatas.datas[0] + 1);
	  m_fullDatas.datas[m_fullDatas.datas.size() - 1] = 0;
	  if (m_pendingDatas.datas.size() != l - &m_pendingDatas.datas[0] + 2)
	    m_pendingDatas.datas.erase(m_pendingDatas.datas.begin(), m_pendingDatas.datas.begin() + strlen(l) - 1);
	  else
	    m_pendingDatas.datas.clear();
	  return Socket::Ok;
	  }*/
      return Socket::Error;
    }
  }
}
