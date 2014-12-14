//
// TcpASIOWriter.cpp for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 17:45:50 2014 Moghrabi Alexandre
// Last update Sat Dec 13 05:14:08 2014 Moghrabi Alexandre
//

#include <iostream>
#include "mognetwork/TcpASIODatas.hh"
#include "mognetwork/TcpASIOWriter.hh"

namespace mognetwork
{
  TcpASIOWriter::TcpASIOWriter() :
    m_running(true)
  {
    m_thread = new Thread(*this, false);
    m_socketList = TcpASIODatas::getInstance()->getSocketList();
    m_timeout.tv_sec = 0;
    m_timeout.tv_usec = 1000;
    m_selector.setTimeout(&m_timeout);
  }

  TcpASIOWriter::~TcpASIOWriter()
  {
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
    for (std::list<TcpSocket*>::iterator it = m_socketList->begin(); it != m_socketList->end(); ++it)
      if ((*it)->havingPendingDatas())
	m_selector.addFdToWrite((*it)->getSocketFD());
  }

  void TcpASIOWriter::run()
  {
    bool hasMoreDatasToSend = false;

    while (m_running)
      {
	if (hasMoreDatasToSend)
	  {
	    setFds();
	    m_selector.waitForTrigger();
	    if (m_selector.getState() == Selector::Error)
	      {
		std::cerr << "Select error on writing thread." << std::endl;
		return ;
	      }
	    std::list<SocketFD> triggeredList = m_selector.getWritingTriggeredSockets();
	    hasMoreDatasToSend = false;
	    for (std::list<SocketFD>::iterator it = triggeredList.begin(); it != triggeredList.end(); ++it)
	      {
		TcpSocket* socket = TcpASIODatas::getInstance()->getSocketByFd(*it);
		if (socket->havingPendingDatas())
		  socket->sendPendingDatas(); // TODO need to verify the return. needed?
		if (socket->havingPendingDatas())
		  hasMoreDatasToSend = true;
	      }
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
