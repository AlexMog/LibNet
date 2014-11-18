//
// TcpSocket.cpp for TcpSocket in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 20:09:34 2014 mognetworkhrabi Alexandre
// Last update Tue Nov 18 19:03:25 2014 Moghrabi Alexandre
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include "TcpSocket.hh"
#include "OsSocket.hh"
#include "Packet.hh"

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
    m_pendingDatas.clear();
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
    std::size_t totalSize;
    std::size_t allreaded = 0;

    // Read the size of the pending packet
    while (readed < sizeof(std::size_t))
      {
	char* data = reinterpret_cast<char*>(&totalSize) + readed;
	Socket::Status status = receive(data, sizeof(std::size_t) - m_pendingRDatas.readed, readed, 0);
	if (status != Ok)
	  return (status);
      }
    // Size is set, let's read the content!
    if (m_pendingRDatas.readed >= sizeof(std::size_t))
      {
	while (allreaded < totalSize)
	  {
	    std::size_t toGet = std::min(static_cast<std::size_t>(totalSize - allreaded), sizeof(buffer));
	    Socket::Status status = receive(buffer, toGet, readed, 0);
	    if (status != Ok)
	      return (status);
	    allreaded += readed;
	    if (readed > 0)
	      {
		data.resize(data.size() + readed);
		char* begin = &data[0] + data.size() - readed;
		std::memcpy(begin, buffer, readed);
	      }
	    if (m_pendingRDatas.readed >= m_pendingRDatas.totalSize)
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
    Data _data;
    _data.resize(size + sizeof(std::size_t));
    std::memcpy(&_data[0], &size, sizeof(std::size_t));
    std::memcpy(&_data[0] + sizeof(std::size_t), &data[0], size);
    m_pendingDatas.push_back(_data);
    return (Ok);
  }

  bool TcpSocket::havingPendingDatas() const
  {
    return (!m_pendingDatas.empty());
  }

  Socket::Status TcpSocket::sendPendingDatas()
  {
    if (!m_pendingDatas.empty())
      {
	int sended;
	DataList::iterator it = m_pendingDatas.begin();
	sended = ::send(getSocketFD(), &(*it)[0], (*it).size(), flags | MSG_DONTWAIT);
	if (sended < 0)
	  return (OsSocket::getErrorStatus());
	if (sended == 0)
	  return (Disconnected);
	std::cout << "test" << std::endl;
	if ((std::size_t)sended == (*it).size())
	  {
	    m_pendingDatas.pop_front();
	    return (sendPendingDatas());
	  }
	Data temp = *it;
	std::size_t waiting = (*it).size() - sended;
	(*it).resize(waiting);
	std::memcpy(&(*it)[0], &temp[0], waiting);
	return (Ok);
      }
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
    m_userData = userData;
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
