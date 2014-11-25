//
// SocketSelector.cpp for SocketSelector in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun 12 18:06:35 2014 mognetworkhrabi Alexandre
// Last update Tue Nov 25 16:50:00 2014 Moghrabi Alexandre
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include "mognetwork/Selector.hh"

namespace mognetwork
{
  Selector::Selector() : m_timeout(NULL), m_maxFds(0) {}
  Selector::~Selector() {}

  void Selector::addFdToWrite(SocketFD fd)
  {
    m_writeSockets.push_front(fd);
    m_maxFds = std::max(m_maxFds, fd);
  }

  void Selector::addFdToRead(SocketFD fd)
  {
    m_readSockets.push_front(fd);
  }

  void Selector::setFds()
  {
    m_maxFds = 0;
    FD_ZERO(&m_rdfs);
    FD_ZERO(&m_wdfs);

    for (std::list<SocketFD>::iterator it = m_readSockets.begin();
	 it != m_readSockets.end(); ++it)
      {
	FD_SET(*it, &m_rdfs);
	m_maxFds = std::max(m_maxFds, *it);
      }

    for (std::list<SocketFD>::iterator it = m_writeSockets.begin();
	 it != m_writeSockets.end(); ++it)
      {
	FD_SET(*it, &m_wdfs);
	m_maxFds = std::max(m_maxFds, *it);
      }
  }

  void Selector::updateFds()
  {
    m_readUpdated.clear();
    m_writeUpdated.clear();
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
    if (select(m_maxFds + 1, &m_rdfs, &m_wdfs, NULL, m_timeout) == -1)
      m_state = Error;
    else
      updateFds();
  }
} // namespace mognetwork
