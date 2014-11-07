//
// Socket.cpp for socket in 
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:22:18 2014 Moghrabi Alexandre
// Last update Wed Oct  8 08:25:17 2014 Moghrabi Alexandre
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include "OsSocket.hh"
#include "Socket.hh"

namespace Mog
{
  Socket::Socket(Type type) :
    m_type(type),
    m_socket(Mog::OsSocket::notValid())
  {}

  Socket::~Socket()
  {
    close();
  }

  SocketFD Socket::getSocketFD() const
  {
    return (m_socket);
  }

  void Socket::create()
  {
    if (m_socket == Mog::OsSocket::notValid())
      {
	SocketFD fd = socket(PF_INET, m_type == Tcp ? SOCK_STREAM : SOCK_DGRAM, 0);
	create(fd);
      }
  }

  void Socket::create(SocketFD fd)
  {
    if (m_socket == Mog::OsSocket::notValid())
      {
	m_socket = fd;
	if (m_type == Tcp)
	  {
	    int yes = 1;
	    if (setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
	      {
		std::cerr << "Cannot set option \"TCP_NODELAY\" on the sockets." << std::endl;
	      }

#ifdef OS_MAC
	    if (setsockopt(m_socket, SOL_SOCKET, SO_NOSIGPIPE, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
	      {
		std::cerr << "Cannot set option \"SO_NOSIGPIPE\" on the socket." << std::endl;
	      }
#endif // OS_MAC
	  }
	else
	  {
	    int yes = 1;
	    if (setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
	      {
		std::cerr << "Failed to enable broadcast on UDP socket." << std::endl;
	      }
	  }
      }
  }

  void Socket::close()
  {
    if (m_socket != Mog::OsSocket::notValid())
      {
	Mog::OsSocket::close(m_socket);
	m_socket = Mog::OsSocket::notValid();
      }
  }
} // namespace Mog
