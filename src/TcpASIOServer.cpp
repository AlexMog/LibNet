//
// TcpASIOServer.hh for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Nov 17 17:38:14 2014 Moghrabi Alexandre
// Last update Tue Jul  7 14:54:41 2015 Moghrabi Alexandre
//

#include "mognetwork/Mutex.hh"
#include "mognetwork/TcpASIOServer.hh"
#include "mognetwork/BinaryProtocolFactory.hpp"
#include "mognetwork/TextProtocolFactory.hpp"
#include "mognetwork/WebsocketProtocolFactory.hpp"

namespace mognetwork
{
  TcpASIOServer::TcpASIOServer(int port, CommunicationProtocolType protocolType)
  {
    m_port = port;
    if (protocolType == Binary)
      m_protocolFactory = new BinaryProtocolFactory;
    else if (protocolType == LinePerLine)
      m_protocolFactory = new TextProtocolFactory((char*)"\n");
    else if (protocolType == Telnet)
      m_protocolFactory = new TextProtocolFactory((char*)"\r\n");
    else if (protocolType == Websocket)
      m_protocolFactory = new WebsocketProtocolFactory;
    else
      m_protocolFactory = NULL;
    init();
  }

  void TcpASIOServer::init()
  {
	  m_serverListener = new TcpASIOListener(this);
	  m_serverWriter = new TcpASIOWriter(this);
	  m_serverListener->setProtocolFactory(m_protocolFactory);
  }

  TcpASIOServer::TcpASIOServer(int port, IProtocolFactory* protocolFactory)
  {
    m_port = port;
    m_protocolFactory = protocolFactory;
	init();
  }

  TcpASIOServer::~TcpASIOServer()
  {
    delete m_serverListener;
    delete m_serverWriter;
    delete m_protocolFactory;
  }

  void TcpASIOServer::start()
  {
    startWithoutJoin();
    join();
  }

  void TcpASIOServer::startWithoutJoin()
  {
	  m_serverSocket.bind(m_port);
	  m_serverSocket.listen(42);
	  m_serverListener->start();
	  m_serverWriter->start();
  }

  void TcpASIOServer::join()
  {
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
