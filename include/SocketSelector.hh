//
// SocketSelector.hh for mognetwork in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Wed Jun 11 15:43:12 2014 mognetworkhrabi Alexandre
// Last update Fri Oct 10 15:52:21 2014 mognetworkhrabi Alexandre
//

#ifndef SOCKETSELECTOR_HH
# define SOCKETSELECTOR_HH

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <list>
#include "SocketSelectorListener.hh"
#include "TcpSocket.hh"

typedef timeval Time;

namespace mognetwork
{
class SocketSelector
{
public:
  enum TriggerType
    {
      None,
      Read,
      Write
    };
  enum State
    {
      Waiting,
      Error
    };
  SocketSelector(TcpSocket& serverSocket, SocketSelectorListener& socketSelectorListener);
  ~SocketSelector();

public:
  void waitForTrigger();

public:
  void setTimeout(Time* timeout) {m_timeout = timeout;}
  Time* getTimeout() const {return (m_timeout);}
  State getState() const {return (m_state);}
  const TcpSocket& getServerSocket() const {return (m_serverSocket);}

private:
  void setFds();
  void acceptClient();
  void handleClients();

private:
  // Timeout of the select
  Time* m_timeout;
  // List of connected sockets
  std::list<TcpSocket> m_sockets;
  // The state of the selector
  State m_state;
  fd_set rdfs;
  fd_set wdfs;
  int m_maxFds;
  TcpSocket& m_serverSocket;
  SocketSelectorListener& m_socketSelectorListener;
};
} // namespace mognetwork

#endif // !SOCKETSELECTOR_HH
