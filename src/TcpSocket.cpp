//
// TcpSocket.cpp for TcpSocket in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 20:09:34 2014 mognetworkhrabi Alexandre
// Last update Mon Mar  9 18:50:19 2015 Moghrabi Alexandre
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
    std::size_t readed = 0;
    char buffer[1024]; // Buffer to get the datas
    std::size_t numReaded = 0;

    ReadedDatas _data = ReadedDatas();
    data.clear();
    // Read the size of the pending packet
    while (readed < sizeof(std::size_t))
      {
	char* d = reinterpret_cast<char*>(&_data.totalSize) + numReaded;
	Socket::Status status = receive(d, sizeof(std::size_t) - _data.readed, readed, 0);
	numReaded += readed;
	if (status != Ok)
	  return (status);
      }
    // Size is set, let's read the content!
    if (numReaded >= sizeof(std::size_t))
      {
	while (_data.readed < _data.totalSize)
	  {
	    std::size_t toGet = std::min(static_cast<std::size_t>(_data.totalSize - _data.readed), sizeof(buffer));
	    Socket::Status status = receive(buffer, toGet, readed, 0);
	    if (status != Ok)
	      return (status);
	    _data.readed += readed;
	    if (readed > 0)
	      {
		data.resize(data.size() + readed);
		char* begin = &data[0] + data.size() - readed;
		std::memcpy(begin, buffer, readed);
	      }
	    if (_data.readed >= _data.totalSize)
	      return (Ok);
	  }
      }
    return (Error);
  }

  Socket::Status TcpSocket::asyncSend(const char* data, std::size_t size)
  {
    if (!data || (size == 0))
      {
	std::cerr << "Cannot send null data" << std::endl;
	return (Error);
      }
    Data* _data = new Data;
    _data->resize(size + sizeof(std::size_t));
    std::memcpy(&_data->front(), &size, sizeof(std::size_t));
    std::memcpy(&_data->front() + sizeof(std::size_t), data, size);
    m_mutex.lock();
    m_pendingDatas.push_back(_data);
    m_mutex.unlock();
    return (Ok);
  }

  bool TcpSocket::havingPendingDatas()
  {
    m_mutex.lock();
    bool status = m_pendingDatas.empty();
    m_mutex.unlock();
    return (status);
  }

  Socket::Status TcpSocket::sendPendingDatas()
  {
    m_mutex.lock();
    if (!m_pendingDatas.empty())
      {
	int sended;
	DataList::iterator it = m_pendingDatas.begin();
	sended = ::send(getSocketFD(), &(*it)->front(), (*it)->size(), flags | MSG_DONTWAIT);
	if (sended < 0) {
	  m_mutex.unlock();
	  return (OsSocket::getErrorStatus());
	}
	if (sended == 0) {
	  m_mutex.unlock();
	  return (Disconnected);
	}
	if ((std::size_t)sended == (*it)->size())
	  {
	    delete *it;
	    m_pendingDatas.pop_front();
	    m_mutex.unlock();
	    return (sendPendingDatas());
	  }
	Data temp;
	temp.resize((*it)->size());
	std::memcpy(&temp[0], &(*it)->front(), (*it)->size());
	std::size_t waiting = (*it)->size() - sended;
	(*it)->resize(waiting);
	std::memcpy(&(*it)->front(), &temp[0], waiting);
	m_mutex.unlock();
	return (Ok);
      }
    m_mutex.unlock();
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
    Data dat;
    dat.resize(size + sizeof(std::size_t));
    std::memcpy(&dat[0], &size, sizeof(std::size_t));
    std::memcpy(&dat[0] + sizeof(std::size_t), data, size);
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
    std::size_t readed;
    char buffer[1024]; // Buffer to get the datas

    // Read the size of the pending packet
    if (m_pendingRDatas.readed < sizeof(std::size_t))
      {
	char* data = reinterpret_cast<char*>(&m_pendingRDatas.totalSize) + m_pendingRDatas.readed;
	Socket::Status status = receive(data, sizeof(std::size_t) - m_pendingRDatas.readed, readed, MSG_DONTWAIT);
	m_pendingRDatas.readed += readed;
	if (status != Ok)
	  return (status);
      }
    // Size is set, let's read the content!
    if (m_pendingRDatas.readed >= sizeof(std::size_t))
      {
	std::size_t toGet = std::min(static_cast<std::size_t>(m_pendingRDatas.totalSize - m_pendingRDatas.datas.size()), sizeof(buffer));
	
	Socket::Status status = receive(buffer, toGet, readed, MSG_DONTWAIT);
	if (status != Ok)
	  return (status);
	m_pendingRDatas.readed += readed;
	if (readed > 0)
	  {
	    m_pendingRDatas.datas.resize(m_pendingRDatas.datas.size() + readed);
	    char* begin = &m_pendingRDatas.datas[0] + m_pendingRDatas.datas.size() - readed;
	    std::memcpy(begin, buffer, readed);
	  }
	if (m_pendingRDatas.readed >= m_pendingRDatas.totalSize)
	  {
	    m_allDataReaded = new ReadedDatas();
	    m_allDataReaded->datas = m_pendingRDatas.datas;
	    m_allDataReaded->readed = m_pendingRDatas.readed;
	    m_allDataReaded->totalSize = m_pendingRDatas.totalSize;
	    m_pendingRDatas = ReadedDatas();
	    return (Ok);
	  }
      }
    return (Waiting);
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

  TcpSocket::ReadedDatas::ReadedDatas() :
    readed(0),
    totalSize(0),
    datas()
  {}
} // namespace mognetwork
