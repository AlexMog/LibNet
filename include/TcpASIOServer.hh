//
// TcpASIOServer.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Sat Nov 15 18:00:03 2014 Moghrabi Alexandre
// Last update Mon Nov 17 14:20:25 2014 Moghrabi Alexandre
//

#include <list>
#include "ITcpASIOListenerHandler.hh"

namespace mognetwork
{
  class TcpASIOServer : ITcpASIOListenerHandler
  {
  public:
    TcpASIOServer();
    ~TcpASIOServer();

  public:
    void start();
    void stop();
    void addListener(ITcpASIOServerListener* listener) {m_listeners.push_back(listeners);}

  private:
    std::list<ITcpASIOServerListener*> m_listeners;
  };
}; // namespace mognetwork
