//
// WinSocket.cpp for Winsocket in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:54:04 2014 mognetworkhrabi Alexandre
// Last update Wed Oct  8 09:09:36 2014 mognetworkhrabi Alexandre
//

#include "OsSocket.hh"
#include <cstring>

#ifdef OS_WINDOWS
namespace mognetwork
{
  sockaddr_in OsSocket::createAddress(uint32_t address, unsigned short port)
  {
    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = htonl(address);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    return (addr);
  }

  SocketFD OsSocket::notValid()
  {
    return (INVALID_SOCKET);
  }

  void OsSocket::close(SocketFD socket)
  {
    closesocket(socket);
  }

  Socket::Status OsSocket::getErrorStatus()
  {
    switch (WSAGetLastError())
      {
      case WSAEWOULDBLOCK :  return (Socket::Nok);
      case WSAEALREADY :     return (Socket::Nok);
      case WSAECONNABORTED : return (Socket::Disconnected);
      case WSAECONNRESET :   return (Socket::Disconnected);
      case WSAETIMEDOUT :    return (Socket::Disconnected);
      case WSAENETRESET :    return (Socket::Disconnected);
      case WSAENOTCONN :     return (Socket::Disconnected);
      case WSAEISCONN :      return (Socket::Done);
      default :              return (Socket::Error);
      }
  }
} // namespace mognetwork
#endif /* OS_WINDOWS */
