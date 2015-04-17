//
// TcpSocket.cpp for TcpSocket in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 20:09:34 2014 mognetworkhrabi Alexandre
// Last update Fri Apr 17 17:10:45 2015 Moghrabi Alexandre
//

#include "mognetwork/OS.hh"

#include <sys/types.h>
#ifndef OS_WINDOWS
#include <sys/socket.h>
#include <netdb.h>
#else
#include <winsock2.h>
#include <Ws2tcpip.h>
#endif // !OS_WINDOWS
#include <algorithm>
#include <cstring>
#include <iostream>
#include "mognetwork/TcpSocket.hh"
#include "mognetwork/OsSocket.hh"
#include "mognetwork/Packet.hh"
#include "mognetwork/AProtocolListener.hh"
#include "mognetwork/LibNetworkException.hh"

namespace
{
#ifdef OS_LINUX
  const int flags = MSG_NOSIGNAL;
#else
  const int flags = 0;
#endif
}

// ! Every packets sends a header (who contains the size of the packet) BEFORE its content.
namespace mognetwork
{
  bool deleteAll(TcpSocket::Data* elem) {delete elem; return true;}

  TcpSocket::TcpSocket() :
    Socket(Tcp), m_userData(NULL)
  {
    // Create the socket, and init it
    create();
  }

  TcpSocket::TcpSocket(SocketFD fd) :
    Socket(Tcp), m_userData(NULL)
  {
    create(fd);
  }

  TcpSocket::~TcpSocket()
  {
    if (m_protocolListener != NULL)
      delete m_protocolListener;
  }

  Socket::Status TcpSocket::connect(const IpAddress& rAddress, unsigned short port)
  {
    // Create the sockaddr by the OS
    sockaddr_in address = OsSocket::createAddress(rAddress.getInt(), port);

    // connect the socket to the address
    return (::connect(getSocketFD(), reinterpret_cast<sockaddr*>(&address), sizeof(address))  == -1 ? OsSocket::getErrorStatus() : Ok);
  }

  void TcpSocket::disconnect()
  {
    close();
    m_pendingDatas.remove_if(deleteAll);
    m_pendingRDatas = ReadedDatas();
  }

  Socket::Status TcpSocket::receive(char* data, std::size_t size, std::size_t& received, int _flags)
  {
    received = 0;
    if (!data)
      {
	std::cerr << "Cannot receive datas if the buffer is null." << std::endl;
	return (Error);
      }
    int readed = recv(getSocketFD(), data, static_cast<int>(size), flags | _flags);
    if (readed > 0)
      {
	received = static_cast<std::size_t>(readed);
	return (Ok);
      }
    else if (readed == 0)
      return (Disconnected);
    else
      return (OsSocket::getErrorStatus());
  }

  Socket::Status TcpSocket::receiveAll(Data& data)
  {
    if (m_protocolListener == NULL)
      throw LibNetworkException("No protocol listener found.", __LINE__, __FILE__);
    return m_protocolListener->onReadAllTrigger(data);
  }

  Socket::Status TcpSocket::asyncSend(const char* data, std::size_t size)
  {
    if (!data || (size == 0))
      {
	std::cerr << "Cannot send null data" << std::endl;
	return (Error);
      }
    if (m_protocolListener == NULL)
      throw LibNetworkException("No protocol listener found.", __LINE__, __FILE__);
    Data* _data = new Data;
    m_protocolListener->onSendDatas(data, size, *_data);
    m_pendingDatas.push_back(_data);
    return (Ok);
  }

  bool TcpSocket::havingPendingDatas()
  {
    m_mutex.lock();
    bool status = !m_pendingDatas.empty();
    m_mutex.unlock();
    return (status);
  }

  Socket::Status TcpSocket::sendPendingDatas()
  {
    //    m_mutex.lock();
    if (!m_pendingDatas.empty())
      {
	int sended;
	DataList::iterator it = m_pendingDatas.begin();
	sended = ::send(getSocketFD(), &(*it)->front(), (*it)->size(), flags);
	if (sended < 0) {
	  //	  m_mutex.unlock();
	  return (OsSocket::getErrorStatus());
	}
	if (sended == 0) {
	  //m_mutex.unlock();
	  return (Disconnected);
	}
	if ((std::size_t)sended == (*it)->size())
	  {
	    delete *it;
	    m_pendingDatas.pop_front();
	    //m_mutex.unlock();
	    return (sendPendingDatas());
	  }
	Data temp;
	temp.resize((*it)->size());
	std::memcpy(&temp[0], &(*it)->front(), (*it)->size());
	std::size_t waiting = (*it)->size() - sended;
	(*it)->resize(waiting);
	std::memcpy(&(*it)->front(), &temp[0], waiting);
	//	m_mutex.unlock();
	return (Ok);
      }
    //    m_mutex.unlock();
    return (Nok);
  }

  // Normal send method, waits until the server has received everything.
  Socket::Status TcpSocket::send(const char* data, std::size_t size)
  {
    int sent;

    if (!data || (size == 0))
      {
	std::cerr << "Cannot send null data" << std::endl;
	return (Error);
      }
    if (m_protocolListener == NULL)
      throw LibNetworkException("No protocol listener found.", __LINE__, __FILE__);
    Data dat;
    m_protocolListener->onSendDatas(data, size, dat);
    sent = ::send(getSocketFD(), &dat[0], dat.size(), 0);
    if (sent < 0)
      return (OsSocket::getErrorStatus());
    if (sent == 0)
      return (Disconnected);
    return (Ok);
  }

  void TcpSocket::setUserData(void* userData)
  {
    m_mutex.lock();
    m_userData = userData;
    m_mutex.unlock();
  }

  void* TcpSocket::getUserData() const
  {
    return (m_userData);
  }

  Socket::Status TcpSocket::readPendingDatas()
  {
    if (m_protocolListener == NULL)
      throw LibNetworkException("No protocol listener found.", __LINE__, __FILE__);

    Socket::Status status = m_protocolListener->onReadTrigger();

    if (m_protocolListener->datasFullyReceived())
      {
	m_allDataReaded = new ReadedDatas();
	m_allDataReaded->datas = m_protocolListener->getReadedDatas().datas;
	m_allDataReaded->readed = m_protocolListener->getReadedDatas().readed;
	m_allDataReaded->totalSize = m_protocolListener->getReadedDatas().totalSize;
	m_protocolListener->flushReader();
	return (Ok);
      }
    return status;
  }

  TcpSocket::ReadedDatas* TcpSocket::getDatasReaded() const
  {
    return (m_allDataReaded);
  }

  void TcpSocket::setServer(TcpASIOServer* server)
  {
    m_mutex.lock();
    m_server = server;
    m_mutex.unlock();
  }

  TcpASIOServer* TcpSocket::getServer() const
  {
    return m_server;
  }

  Packet* TcpSocket::getPacketReaded()
  {
    return new Packet(m_allDataReaded);
  }

  void TcpSocket::getPacketReaded(Packet& packet)
  {
    packet.reinitialize(m_allDataReaded);
  }

  TcpSocket::ReadedDatas::ReadedDatas() :
    readed(0),
    totalSize(0),
    datas()
  {}
} // namespace mognetwork
