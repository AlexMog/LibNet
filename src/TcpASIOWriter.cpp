//
// TcpASIOWriter.cpp for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 17:45:50 2014 Moghrabi Alexandre
// Last update Wed Mar 25 16:09:06 2015 Moghrabi Alexandre
//

#include <iostream>
#include "mognetwork/TcpASIOWriter.hh"
#include "mognetwork/TcpASIOServer.hh"

namespace mognetwork
{
  TcpASIOWriter::TcpASIOWriter() :
    m_running(true),
    m_mutex(new Mutex()),
    m_socketList(new std::list<TcpSocket*>()),
    m_server(NULL)
  {
    init();
  }

  void TcpASIOWriter::init()
  {
	m_thread = new Thread(*this, false);
    m_timeout.tv_sec = 0;
    m_timeout.tv_usec = 1000;
	m_selector.setTimeout(&m_timeout);
  }

  TcpASIOWriter::TcpASIOWriter(TcpASIOServer* server) :
    m_running(true),
    m_mutex(&server->getMutex()),
    m_socketList(&server->getSocketList()),
    m_server(server)
  {
    init();
  }

  TcpASIOWriter::~TcpASIOWriter()
  {
    if (m_server == NULL) {
      if (m_mutex != NULL)
	delete (m_mutex);
      if (m_socketList != NULL)
	delete (m_socketList);
    }
    delete (m_thread);
  }

  void TcpASIOWriter::stop()
  {
    m_running = false;
    m_condVar.signal();
  }

  void TcpASIOWriter::wait()
  {
    m_thread->join();
  }

  void TcpASIOWriter::start()
  {
    m_thread->start();
  }

  void TcpASIOWriter::setFds()
  {
    m_selector.clearFdToWrite();
    for (std::list<TcpSocket*>::iterator it = m_socketList->begin(); it != m_socketList->end(); ++it) {
      if ((*it)->havingPendingDatas())
	m_selector.addFdToWrite((*it)->getSocketFD());
    }
  }

  void TcpASIOWriter::run()
  {
    bool hasMoreDatasToSend = false;

    while (m_running)
      {
	if (hasMoreDatasToSend)
	  {
	    m_mutex->lock();
	    setFds();
	    m_mutex->unlock();
	    m_selector.waitForTrigger();
	    if (m_selector.getState() == Selector::Error)
	      {
		std::cerr << "Select error on writing thread." << std::endl;
		return ;
	      }
	    m_mutex->lock();
	    std::list<SocketFD> triggeredList = m_selector.getWritingTriggeredSockets();
	    hasMoreDatasToSend = false;
	    for (std::list<SocketFD>::iterator it = triggeredList.begin(); it != triggeredList.end(); ++it)
	      {
		TcpSocket* socket = m_server->getSocketByFd(*it);
		if (socket->havingPendingDatas())
		  socket->sendPendingDatas();
		if (socket->havingPendingDatas())
		  hasMoreDatasToSend = true;
	      }
	    m_mutex->unlock();
	  }
	else
	  {
	    m_condVar.wait();
	    hasMoreDatasToSend = true;
	  }
      }
    std::cout << "Writer thread stopped." << std::endl;
  }
} // namespace mognetwork
