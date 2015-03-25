//
// TcpASIOServer.hh for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Nov 17 17:38:14 2014 Moghrabi Alexandre
// Last update Wed Mar 25 16:16:40 2015 Moghrabi Alexandre
//

#include "mognetwork/Mutex.hh"
#include "mognetwork/TcpASIOServer.hh"

namespace mognetwork
{
  TcpASIOServer::TcpASIOServer(int port)
  {
    m_serverListener = new TcpASIOListener(this);
    m_serverWriter = new TcpASIOWriter(this);
    m_port = port;
  }

  TcpASIOServer::~TcpASIOServer()
  {
    delete m_serverListener;
    delete m_serverWriter;
  }

  void TcpASIOServer::start()
  {
    m_serverSocket.bind(m_port);
    m_serverSocket.listen(42);
    m_serverListener->start();
    m_serverWriter->start();
    m_serverWriter->wait();
    m_serverListener->wait();
    m_serverSocket.disconnect();
  }

  void TcpASIOServer::stop()
  {
    m_serverWriter->stop();
    m_serverListener->stop();
  }

  TcpSocket* TcpASIOServer::getSocketByFd(SocketFD fd)
  {
    for (std::list<TcpSocket*>::iterator it = m_socketList.begin(); it != m_socketList.end(); ++it)
      if ((*it)->getSocketFD() == fd)
	return *it;
    return NULL;
  }

  void TcpASIOServer::remSocket(SocketFD socket)
  {
    for (std::list<TcpSocket*>::iterator it = m_socketList.begin(); it != m_socketList.end();)
      {
	if ((*it)->getSocketFD() == socket)
	  {
	    TcpSocket* value = *it;
	    (*it)->disconnect();
	    it = m_socketList.erase(it);
	    delete value;
	  }
	else
	  ++it;
      }
  }
} // namespace mognetwork
