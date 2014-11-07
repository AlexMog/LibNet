//
// WinSocket.hh for WinSocket in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:43:05 2014 mognetworkhrabi Alexandre
// Last update Fri Jun  6 11:16:04 2014 mognetworkhrabi Alexandre
//

#ifndef WINSOCKET_HH
# define WINSOCKET_HH

#ifdef _WIN32_WINDOWS
  #undef _WIN32_WINDOWS
#endif
#ifdef _WIN32_WINNT
  #undef _WIN32_WINNT
#endif
#define _WIN32_WINDOWS 0x0501
#define _WIN32_WINNT 0x0501
#include "SocketFD.hh"
#include "Socket.hh"
#include <winsock2.h>
#include <ws2tcpip.h>

namespace mognetwork
{
class OsSocket
{
public:
  typedef int AddreLength;
  static sockaddr_in createAddress(Uint32 address, unsigned short port);
  static SocketFD notValid();
  static void close(SocketFD socket);
  static Socket::Status getErrorStatus();
};
} // namespace mognetwork

#endif // !WINSOCKET_HH
