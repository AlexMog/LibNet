//
// TcpASIOListener.cpp for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Thu Nov 13 13:19:05 2014 Moghrabi Alexandre
// Last update Thu Nov 20 15:29:26 2014 Moghrabi Alexandre
//

#include "TcpASIODatas.hh"
#include "LibNetworkException.hh"
#include "TcpASIOListener.hh"

namespace mognetwork
{
  TcpASIOListener::TcpASIOListener(TcpServerSocket& serverSocket) :
    m_running(true), m_serverSocket(serverSocket)
  {
    m_thread = new Thread(*this, false);
    if (pipe(m_pipefd) != 0)
      throw LibNetworkException("Pipe creation failed.", __LINE__, __FILE__);
    m_socketList = TcpASIODatas::getInstance()->getSocketList();
  }

  TcpASIOListener::~TcpASIOListener()
  {
    delete m_thread;
  }

  void TcpASIOListener::start()
  {
    m_selector.addFdToRead(m_serverSocket.getSocketFD());
    m_selector.addFdToRead(m_pipefd[0]);
    m_thread->start();
  }

  void TcpASIOListener::stop()
  {
    m_running = false;
    write(m_pipefd[1], "0", 1);
  }

  void TcpASIOListener::wait()
  {
    m_thread->join();
  }

  void TcpASIOListener::acceptClient()
  {
    TcpSocket* cSocket;
    if ((cSocket = m_serverSocket.accept()) == NULL)
      {
	std::cerr << "A client cannot be accepted." << std::endl;
	return ;
      }
    m_selector.addFdToRead(cSocket->getSocketFD());
    TcpASIODatas::getInstance()->addSocket(cSocket);
    for (std::list<ITcpASIOListenerHandler*>::iterator it = m_listeners.begin(); it != m_listeners.end(); ++it)
      (*it)->onConnect(*cSocket);
  }

  void TcpASIOListener::run()
  {
    while (m_running)
      {
	m_selector.waitForTrigger();
	if (m_selector.getState() == Selector::Error)
	  {
	    std::cerr << "Select error on listening thread." << std::endl;
	    return ;
	  }
	std::list<SocketFD> triggeredList = m_selector.getReadingTriggeredSockets();
	for (std::list<SocketFD>::iterator it = triggeredList.begin(); it != triggeredList.end(); ++it)
	  {
	    if (*it == m_serverSocket.getSocketFD())
	      {
		// NEW CLIENT TO ACCEPT
		acceptClient();
	      }
	    else if (*it == m_pipefd[0])
	      {
		char buffer[2];
		read(m_pipefd[0], buffer, 1);
	      }
	    else
	      {
		TcpSocket* socket = TcpASIODatas::getInstance()->getSocketByFd(*it);
		Socket::Status status = socket->readPendingDatas();
		if (status == Socket::Ok)
		  {
		    // DATAS FULLY RECEIVED.
		    for (std::list<ITcpASIOListenerHandler*>::iterator it2 = m_listeners.begin();
			 it2 != m_listeners.end(); ++it2)
		      (*it2)->onReceivedData(*socket);
		  }
		else if (status != Socket::Waiting)
		  {
		    // DISCONNECTED
		    for (std::list<ITcpASIOListenerHandler*>::iterator it2 = m_listeners.begin();
			 it2 != m_listeners.end(); ++it2)
		      (*it2)->onDisconnect(*socket);
		    m_selector.remFdToRead(*it);
		    TcpASIODatas::getInstance()->remSocket(*it);
		  }
	      }
	  }
      }
  }
} // namespace mognetwork
