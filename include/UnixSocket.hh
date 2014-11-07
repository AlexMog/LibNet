//
// UnixSocket.hh for UnixSocket.hh in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:36:40 2014 mognetworkhrabi Alexandre
// Last update Wed Oct  8 08:11:47 2014 mognetworkhrabi Alexandre
//

#ifndef UNIXSOCKET_HH
# define UNIXSOCKET_HH

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netinet/tcp.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <unistd.h>
# include "SocketFD.hh"
# include "Socket.hh"

namespace mognetwork
{
class OsSocket
{
public:
  typedef socklen_t AddrLength;
  static sockaddr_in createAddress(uint32_t address, unsigned short port);
  static SocketFD notValid();
  static void close(SocketFD socket);
  static Socket::Status getErrorStatus();
};
} // namespace mognetwork

#endif // !UNIXSOCKET_HH
