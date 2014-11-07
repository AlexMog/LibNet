//
// SocketSelector.cpp for SocketSelector in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun 12 18:06:35 2014 mognetworkhrabi Alexandre
// Last update Fri Oct 10 15:59:30 2014 mognetworkhrabi Alexandre
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include "SocketSelector.hh"

namespace mognetwork
{
  SocketSelector::SocketSelector(TcpSocket& serverSocket,
				 SocketSelectorListener& socketSelectorListener) :
    m_timeout(NULL), m_maxFds(0), m_serverSocket(serverSocket),
    m_socketSelectorListener(socketSelectorListener)
  {}
  SocketSelector::~SocketSelector() {}

  void SocketSelector::acceptClient()
  {
    sockaddr_in	csin;
    memset(&csin, 0, sizeof(csin));
    socklen_t sinsize = sizeof(csin);
    SocketFD cSocket;
    if ((cSocket = ::accept(m_serverSocket.getSocketFD(), (sockaddr *)&csin,
			    &sinsize)) == -1)
      {
	std::cerr << "Cannot accept a client." << std::endl;
	return ;
      }
    TcpSocket socket(cSocket);
    m_maxFds = std::max(m_maxFds, cSocket);
    m_sockets.push_front(socket);
    FD_SET(cSocket, &rdfs);
    std::cout << "Accepted new client." << std::endl;
  }

  void SocketSelector::setFds()
  {
    FD_ZERO(&rdfs);
    FD_ZERO(&wdfs);
    FD_SET(m_serverSocket.getSocketFD(), &rdfs);
    for (std::list<TcpSocket>::iterator it = m_sockets.begin();
	 it != m_sockets.end(); ++it)
      {
	FD_SET(it->getSocketFD(), &rdfs);
	if (it->havingPendingDatas())
	  FD_SET(it->getSocketFD(), &wdfs);
      }
  }

  void SocketSelector::handleClients()
  {
    for (std::list<TcpSocket>::iterator it = m_sockets.begin();
	 it != m_sockets.end();)
      {
	if (FD_ISSET(it->getSocketFD(), &rdfs))
	  {
	    bool inc = true;
	    Socket::Status status = it->readPendingDatas();
	    if (status == Socket::Ok)
	      {
		// DATAS FULLY RECEIVED.
		m_socketSelectorListener.clientDatasReceived(*it);
	      }
	    else if (status != Socket::Waiting)
	      {
		// DISCONNECTED
		it->disconnect();
		m_socketSelectorListener.clientDisconnected(*it);
		it = m_sockets.erase(it);
		inc = false;
	      }
	    if (inc)
	      ++it;
	  }
	if (FD_ISSET(it->getSocketFD(), &wdfs))
	  it->sendPendingDatas();
      }
  }

  void SocketSelector::waitForTrigger()
  {
    m_state = Waiting;
    setFds();    
    if (select(m_maxFds, &rdfs, &wdfs, NULL, m_timeout) == -1)
      {
	m_state = Error;
	return ;
      }
    if (FD_ISSET(m_serverSocket.getSocketFD(), &rdfs)) // New client connected
      acceptClient();
    else
      handleClients();
  }
} // namespace mognetwork
