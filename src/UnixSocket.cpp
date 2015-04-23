//
// UnixSocket.cpp for UnixSocket in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:47:33 2014 mognetworkhrabi Alexandre
// Last update Tue Nov 25 16:48:39 2014 Moghrabi Alexandre
//

#include "mognetwork/OS.hh"
#ifndef OS_WINDOWS
#include "mognetwork/UnixSocket.hh"
#include <errno.h>
#include <fcntl.h>
#include <cstring>

namespace mognetwork
{
  sockaddr_in OsSocket::createAddress(uint32_t address, unsigned short port)
  {
    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = htonl(address);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
#if defined(OS_MAC)
    addr.sin_len = sizeof(addr);
#endif // !OS_MAC
    return (addr);
  }

  SocketFD OsSocket::notValid()
  {
    return (-1);
  }

  void OsSocket::close(SocketFD socket)
  {
    ::close(socket);
  }

  Socket::Status OsSocket::getErrorStatus()
  {
    if ((errno == EAGAIN) || (errno == EINPROGRESS))
      return (Socket::Nok);
    switch (errno)
      {
      case EWOULDBLOCK:	 return (Socket::Nok);
      case ECONNABORTED: return (Socket::Disconnected);
      case ECONNRESET:   return (Socket::Disconnected);
      case ETIMEDOUT:    return (Socket::Disconnected);
      case ENETRESET:    return (Socket::Disconnected);
      case ENOTCONN:     return (Socket::Disconnected);
      case EPIPE:        return (Socket::Disconnected);
      default:           return (Socket::Error);
      }
  }
} // namespace mognetwork
#endif // !OS_WINDOWS