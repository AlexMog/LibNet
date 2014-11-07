//
// Selector.hh for mognetwork in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Wed Jun 11 15:43:12 2014 mognetworkhrabi Alexandre
// Last update Fri Nov  7 21:54:41 2014 Moghrabi Alexandre
//

#ifndef SELECTOR_HH
# define SELECTOR_HH

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <list>
#include "SocketFD.hh"

typedef timeval Time;

namespace mognetwork
{
class Selector
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
  Selector();
  ~Selector();

public:
  void waitForTrigger();

public:
  Time* getTimeout() const {return m_timeout;}
  State getState() const {return m_state;}
  const std::list<SocketFD>& getWrintingTriggeredSockets() const {return m_writeUpdated;}
  const std::list<SocketFD>& getReadingTriggeredSockets() const {return m_readUpdated;}

public:
  void setTimeout(Time* timeout) {m_timeout = timeout;}
  void addFdToWrite(SocketFD fd);
  void addFdToRead(SocketFD fd);
  void remFdToWrite(SocketFD fd) {m_writeSockets.remove(fd);}
  void remFdToRead(SocketFD fd) {m_readSockets.remove(fd);}

private:
  void setFds();
  void updateFds();

private:
  // Timeout of the select
  Time* m_timeout;
  // List of socketFds to monitor
  std::list<SocketFD> m_readSockets;
  std::list<SocketFD> m_writeSockets;
  // List of sockets who got modified
  std::list<SocketFD> m_readUpdated;
  std::list<SocketFD> m_writeUpdated;
  // The state of the selector
  State m_state;
  fd_set m_rdfs;
  fd_set m_wdfs;
  int m_maxFds;
};
} // namespace mognetwork

#endif // !SELECTOR_HH
