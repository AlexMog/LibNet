//
// TcpASIOListener.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Nov 10 18:10:20 2014 Moghrabi Alexandre
// Last update Tue Nov 11 17:30:39 2014 Moghrabi Alexandre
//

#ifndef TCPASIOLISTENER_HH_
# define TCPASIOLISTENER_HH_

# include <unistd.h>
# include "TcpSocket.hh"
# include "ITcpASIOListenerHandler.hh"

namespace mognetwork
{
  class TcpASIOListener
  {
  public:
    TcpASIOListener(const TcpSocket& serverSocket, const TcpASIOListenerHandler& handler);
    ~TcpASIOListener();

  public:
    const int* getPipeFds() const {return pipefds;}

  public:
    void init();
    void start();
    void stop();
    void wait();

  private:
    const TcpSocket& m_serverSocket;
    const ITcpASIOListenerHandler& m_handler;
    int m_pipefds[2];
    int m_maxFds;
  };
}; // namespace mognetwork

#endif // !TCPASIOLISTENER_HH_
