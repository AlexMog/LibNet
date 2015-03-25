//
// TcpASIOListener.cpp for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Thu Nov 13 13:19:05 2014 Moghrabi Alexandre
// Last update Wed Mar 25 16:16:17 2015 Moghrabi Alexandre
//

#include "mognetwork/LibNetworkException.hh"
#include "mognetwork/TcpASIOListener.hh"
#include "mognetwork/TcpASIOServer.hh"

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
    if (pipe(m_pipefd) != 0)
      throw LibNetworkException("Pipe creation failed.", __LINE__, __FILE__);
    m_timeout.tv_sec = 0;
    m_timeout.tv_usec = 100000;
    m_selector.setTimeout(NULL);
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


  TcpASIOListener::~TcpASIOListener()
  {
    if (m_server == NULL)
      {
	if (m_mutex != NULL)
	  delete (m_mutex);
	if (m_socketList != NULL)
	  delete (m_socketList);
      }
    ::close(m_pipefd[0]);
    ::close(m_pipefd[1]);
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
