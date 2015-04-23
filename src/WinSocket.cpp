//
// WinSocket.cpp for Winsocket in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:54:04 2014 mognetworkhrabi Alexandre
// Last update Tue Nov 25 16:48:25 2014 Moghrabi Alexandre
//

#include "mognetwork/OS.hh"

#ifdef OS_WINDOWS

#include <iostream>
#include "mognetwork/OsSocket.hh"
#include <cstring>

namespace mognetwork
{
  sockaddr_in OsSocket::createAddress(UINT32 address, unsigned short port)
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
      case WSAEISCONN :      return (Socket::Ok);
      default :              return (Socket::Error);
      }
  }

  // Windows needs an initialisation to use socket
  // So we are going to create a class that does it automaticly.
  // Thanks to the SFML sources for the help.
  struct LibNetInit
  {
	  LibNetInit()
	  {
		  WSADATA init;
		  WSAStartup(MAKEWORD(2, 2), &init);
	  }

	  ~LibNetInit()
	  {
		  WSACleanup();
	  }
  };
  LibNetInit globalLibNetInit;
} // namespace mognetwork
#endif /* OS_WINDOWS */
