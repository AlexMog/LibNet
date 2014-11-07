//
// SocketSelector.cpp for SocketSelector in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun 12 18:06:35 2014 mognetworkhrabi Alexandre
// Last update Fri Nov  7 21:57:31 2014 Moghrabi Alexandre
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include "Selector.hh"

namespace mognetwork
{
  Selector::Selector() {}
  Selector::~Selector() {}

  void Selector::addFdToWrite(SocketFD fd)
  {
    m_writeSockets.push_front(fd);
    m_maxFds = std::max(m_maxFds, fd);
  }

  void Selector::addFdToRead(SocketFD fd)
  {
    m_writeSockets.push_front(fd);
    m_maxFds = std::max(m_maxFds, fd);
  }

  void Selector::setFds()
  {
    FD_ZERO(&m_rdfs);
    FD_ZERO(&m_wdfs);

    for (std::list<SocketFD>::iterator it = m_readSockets.begin();
	 it != m_readSockets.end(); ++it)
	FD_SET(*it, &m_rdfs);

    for (std::list<SocketFD>::iterator it = m_writeSockets.begin();
	 it != m_writeSockets.end(); ++it)
	FD_SET(*it, &m_wdfs);
  }

  void Selector::updateFds()
  {
    m_readSockets.clear();
    m_writeSockets.clear();
    for (std::list<SocketFD>::iterator it = m_readSockets.begin();
	 it != m_readSockets.end(); ++it)
      if (FD_ISSET(*it, &m_rdfs))
	m_readUpdated.push_front(*it);
    for (std::list<SocketFD>::iterator it = m_writeSockets.begin();
	 it != m_writeSockets.end(); ++it)
      if (FD_ISSET(*it, &m_wdfs))
	m_writeUpdated.push_front(*it);
  }

  void Selector::waitForTrigger()
  {
    m_state = Waiting;
    setFds();    
    if (select(m_maxFds, &m_rdfs, &m_wdfs, NULL, m_timeout) == -1)
      m_state = Error;
    else
      updateFds();
  }
} // namespace mognetwork
