//
// TcpASIOServer.hh for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Nov 17 17:38:14 2014 Moghrabi Alexandre
// Last update Mon Nov 17 18:27:09 2014 Moghrabi Alexandre
//

#include "TcpASIOServer.hh"

namespace mognetwork
{
  TcpASIOServer::TcpASIOServer(int port)
  {
    m_serverListener = new TcpASIOListener(m_serverSocket);
    m_serverWriter = new TcpASIOWriter();
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
  }

  void TcpASIOServer::stop()
  {
    m_serverWriter->stop();
    m_serverListener->stop();
    m_serverSocket.disconnect();
  }
}; // namespace mognetwork
