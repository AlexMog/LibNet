//
// TcpASIOWriter.cpp for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 17:45:50 2014 Moghrabi Alexandre
// Last update Wed Nov 12 19:31:11 2014 Moghrabi Alexandre
//

#include "TcpASIODatas.hh"
#include "TcpASIOWriter.hh"

namespace mognetwork
{
  TcpASIOWriter::TcpASIOWriter(const TcpSocket& serverSocket) :
    m_serverSocket(serverSocket)
  {
    m_thread = new Thread(*m_runner, false);
    m_runner = new Runner(*this);
    m_socketList = static_cast<TcpASIODatas*>(TcpASIODatas::getInstance())->getSocketList();
  }

  TcpASIOWriter::~TcpASIOWriter()
  {
    delete (m_runner);
    delete (m_thread);
  }

  void TcpASIOWriter::stop()
  {
    m_runner->m_running = false;
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
	m_selector.addFdToRead((*it)->getSocketFD());
  }

  void TcpASIOWriter::Runner::run()
  {
    bool hasMoreDatasToSend = false;

    while (m_running)
      {
	if (hasMoreDatasToSend)
	  {
	    m_parent.setFds();
	    m_parent.getSelector().waitForTrigger();
	    std::list<SocketFD> triggeredList = m_parent.getSelector().getWritingTriggeredSockets();
	    hasMoreDatasToSend = false;
	    for (std::list<SocketFD>::iterator it = triggeredList.begin(); it != triggeredList.end(); ++it)
	      {
		TcpSocket* socket = static_cast<TcpASIODatas*>(TcpASIODatas::getInstance())->getSocketByFd(*it);
		if (socket->havingPendingDatas())
		  socket->sendPendingDatas(); // TODO need to verify the return.
		if (socket->havingPendingDatas())
		  hasMoreDatasToSend = true;
	      }
	  }
	else
	  {
	    m_parent.getCondVar().wait();
	    hasMoreDatasToSend = true;
	  }
      }
  }
}; // namespace mognetwork
