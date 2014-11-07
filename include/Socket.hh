//
// Socket.hh for Network in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:07:37 2014 mognetworkhrabi Alexandre
// Last update Fri Oct 10 15:53:48 2014 mognetworkhrabi Alexandre
//

#ifndef SOCKET_HH
#define SOCKET_HH

#include "SocketFD.hh"

namespace mognetwork
{
class Socket
{
public:
  enum Status
    {
      Ok, // Socket ready to read / send datas
      Nok, // Socket not ready to read / send datas
      Disconnected, // Socket disconnected
      Waiting, // Waiting for datas
      Error // Unexpected error
    };

public:
  virtual ~Socket();
  SocketFD getSocketFD() const;

protected:
  enum Type
    {
      Tcp,
      Udp
    };
  Socket(Type type);
  void create();
  void create(SocketFD fd);
  void close();

private:
  Type m_type;
  SocketFD m_socket;
};
} // namespace mognetwork

#endif /* !SOCKET_HH */
