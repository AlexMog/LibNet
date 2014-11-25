//
// UnixSocket.hh for UnixSocket.hh in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:36:40 2014 mognetworkhrabi Alexandre
// Last update Tue Nov 18 13:07:39 2014 Moghrabi Alexandre
//

#ifndef MOGNETWORK_UNIXSOCKET_HH
# define MOGNETWORK_UNIXSOCKET_HH

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

#endif // !MOGNETWORK_UNIXSOCKET_HH
