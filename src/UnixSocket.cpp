//
// UnixSocket.cpp for UnixSocket in 
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:47:33 2014 Moghrabi Alexandre
// Last update Wed Oct  8 08:02:04 2014 Moghrabi Alexandre
//

#include "UnixSocket.hh"
#include <errno.h>
#include <fcntl.h>
#include <cstring>

namespace Mog
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
} // namespace Mog
