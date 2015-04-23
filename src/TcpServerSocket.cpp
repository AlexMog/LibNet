//
// TcpServerSocket.cpp for LibNet in /home/alexmog/projets/LibNet
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Nov 17 17:51:00 2014 Moghrabi Alexandre
// Last update Tue Nov 25 16:49:20 2014 Moghrabi Alexandre
//

#include <sys/types.h>
#include "mognetwork/OS.hh"
#ifndef OS_WINDOWS
#include <sys/socket.h>
#include <netinet/in.h>
#else
#include <winsock2.h>
#include <Ws2tcpip.h>
#endif // !OS_WINDOWS
#include <string.h>
#include "mognetwork/LibNetworkException.hh"
#include "mognetwork/TcpServerSocket.hh"

namespace mognetwork
{
  TcpServerSocket::TcpServerSocket() : m_bound(false), m_listening(false) {}

  TcpServerSocket::~TcpServerSocket() {}

  TcpSocket* TcpServerSocket::accept()
  {
    sockaddr_in csin;
    memset(&csin, 0, sizeof(csin));
    socklen_t sinsize = sizeof(csin);
    SocketFD cSocket;
    if ((cSocket = ::accept(getSocketFD(), (sockaddr*)&csin, &sinsize)) == -1)
      return NULL;
    return new TcpSocket(cSocket);
  }

  void TcpServerSocket::bind(int port)
  {
    sockaddr_in sin;
#ifndef OS_WINDOWS
    int y = 1;
#else
	const char y = 1;
#endif // !OS_WINDOWS
    memset(&sin, 0, sizeof(sin));
    if (setsockopt(getSocketFD(), SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int)) == -1)
      throw LibNetworkException("setsockopt() error.", __LINE__, __FILE__);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;
    if (::bind(getSocketFD(), (struct sockaddr*)&sin, sizeof(sin)) == -1)
      throw LibNetworkException("bind() error.", __LINE__, __FILE__);
    m_bound = true;
  }

  void TcpServerSocket::listen(int maxWaitingList)
  {
    if (::listen(getSocketFD(), maxWaitingList) == -1)
      throw LibNetworkException("listen() error.", __LINE__, __FILE__);
    m_listening = true;
  }
} // namespace mognetwork
