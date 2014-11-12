//
// TcpASIODatas.cpp for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 18:39:26 2014 Moghrabi Alexandre
// Last update Wed Nov 12 19:16:26 2014 Moghrabi Alexandre
//

#include "TcpASIODatas.hh"

namespace mognetwork
{
  TcpASIODatas::TcpASIODatas()
  {
    m_socketList = new std::list<TcpSocket*>;
  }

  TcpASIODatas::~TcpASIODatas()
  {
    delete m_socketList;
  }

  TcpASIODatas::remSocket(SocketFD socket)
  {
    for (std::list<TcpSocket*>::iterator it = m_socketList.begin(); it != m_socketList.end();)
      {
	if ((*it)->getSocketFD == socket)
	  it = m_socketList.remove(it);
	else
	  ++it;
      }
  }

  TcpSocket* TcpASIODatas::getSocketByFd(SocketFD fd)
  {
    for (std::list<TcpSocket*>::iterator it = m_socketList.begin(); it != m_socketList.end();)
      if ((*it)->getSocketFD == socket)
	return *it;
    return NULL;
  }
}; // namespace mognetwork
