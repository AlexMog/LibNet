//
// TcpASIOListener.cpp for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Thu Nov 13 13:19:05 2014 Moghrabi Alexandre
// Last update Tue Jul  7 14:53:16 2015 Moghrabi Alexandre
//

#include "mognetwork/OS.hh"
#ifdef OS_WINDOWS
#include <fcntl.h>
#include <io.h>
#endif // OS_WINDOWS
#include "mognetwork/LibNetworkException.hh"
#include "mognetwork/TcpASIOListener.hh"
#include "mognetwork/TcpASIOServer.hh"
#include "mognetwork/IProtocolFactory.hh"

namespace mognetwork
{
  TcpASIOListener::TcpASIOListener(TcpServerSocket& serverSocket) :
    m_running(true),
    m_socketList(new std::list<TcpSocket*>),
    m_mutex(new Mutex()),
    m_serverSocket(serverSocket),
    m_server(NULL)
  {
    init();
  }

  void TcpASIOListener::init()
  {
    m_thread = new Thread(*this, false);
#ifndef OS_WINDOWS
    if (pipe(m_pipefd) != 0)
#else
      if (_pipe(m_pipefd, 42, O_BINARY) != 0)
#endif // !OS_WINDOWS
	throw LibNetworkException("Pipe creation failed.", __LINE__, __FILE__);
    m_timeout.tv_sec = 0;
    m_timeout.tv_usec = 10000000;
    //    m_selector.setTimeout(NULL);
  }

  TcpASIOListener::TcpASIOListener(TcpASIOServer* server) :
    m_running(true),
    m_socketList(&server->getSocketList()),
    m_mutex(&server->getMutex()),
    m_serverSocket(server->getServerSocket()),
    m_server(server)
  {
    init();
  }

  void TcpASIOListener::setProtocolFactory(IProtocolFactory* protocolFactory)
  {
    m_protocolFactory = protocolFactory;
  }

  TcpASIOListener::~TcpASIOListener()
  {
    if (m_server == NULL)
      {
	if (m_mutex != NULL)
	  delete (m_mutex);
	if (m_socketList != NULL)
	  delete (m_socketList);
      }
#ifndef OS_WINDOWS
    ::close(m_pipefd[0]);
    ::close(m_pipefd[1]);
#else
	_close(m_pipefd[0]);
	_close(m_pipefd[1]);
#endif // !OS_WINDOWS
    delete m_thread;
  }

  void TcpASIOListener::start()
  {
    m_selector.addFdToRead(m_serverSocket.getSocketFD());
#ifndef OS_WINDOWS
	//TODO Find a solution for windows
	m_selector.addFdToRead(m_pipefd[0]);
#endif // !OS_WINDOWS
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
    cSocket->setProtocolListener(m_protocolFactory->getNewObject(cSocket));
    cSocket->setServer(m_server);
    m_selector.addFdToRead(cSocket->getSocketFD());
    m_server->addSocket(cSocket);
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
		m_mutex->lock();
		// NEW CLIENT TO ACCEPT
		acceptClient();
		m_mutex->unlock();
	      }
	    else if (*it != m_pipefd[0])
	      {
		m_mutex->lock();
		TcpSocket* socket = m_server->getSocketByFd(*it);
		socket->setServer(m_server);
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
		    m_server->remSocket(*it);
		  }
		m_mutex->unlock();
	      }
	  }
      }
    std::cout << "Listener Thread stopped." << std::endl;
  }
} // namespace mognetwork
