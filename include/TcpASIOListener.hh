//
// TcpASIOListener.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Nov 10 18:10:20 2014 Moghrabi Alexandre
// Last update Mon Nov 17 14:20:35 2014 Moghrabi Alexandre
//

/*!
 * \file TcpASIOListener.hh
 * \brief Permet la gestion de la lecture de données en ASIO
 * \author AlexMog
 * \version 0.1
 * \depreciated non terminé
 */

#ifndef TCPASIOLISTENER_HH_
# define TCPASIOLISTENER_HH_

# include <list>
# include <unistd.h>
# include "IRunnable.hh"
# include "Thread.hh"
# include "TcpSocket.hh"
# include "Selector.hh"
# include "ITcpASIOListenerHandler.hh"

namespace mognetwork
{
  class TcpASIOListener : private IRunnable
  {
  public:
    TcpASIOListener(TcpSocket& serverSocket);
    virtual ~TcpASIOListener();

  public:
    void start();
    void stop();
    void wait();

  public:
    void addListener(ITcpASIOListenerHandler* listener) {m_listeners.push_back(listener);}

  public:
    bool isRunning() const {return m_running;}

  public:
    void run();

  private:
    void acceptClient();

  public:
    Selector& getSelector() {return m_selector;}

  private:
    bool m_running;
    std::list<ITcpASIOListenerHandler*> m_listeners;
    Selector m_selector;
    Thread* m_thread;
    std::list<TcpSocket*>* m_socketList;
    int m_pipefd[2];
    TcpSocket& m_serverSocket;
  };
}; // namespace mognetwork

#endif // !TCPASIOLISTENER_HH_
