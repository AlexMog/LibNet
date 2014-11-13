//
// TcpASIOWriter.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 17:35:53 2014 Moghrabi Alexandre
// Last update Thu Nov 13 10:52:20 2014 Moghrabi Alexandre
//

#ifndef TCPASIOWRITER_HH_
# define TCPASIOWRITER_HH_

# include "TcpSocket.hh"
# include "SocketFD.hh"
# include "Selector.hh"
# include "CondVar.hh"
# include "Thread.hh"
# include "IRunnable.hh"
# include <list>

namespace mognetwork
{
  class TcpASIOWriter : private IRunnable
  {
  public:
    TcpASIOWriter();
    virtual ~TcpASIOWriter();

  public:
    void start();
    void stop();
    void wait();

  private:
    void setFds();

  public:
    bool isRunning() const {return m_running;}

  public:
    void run();

  private:
    Selector& getSelector() {return m_selector;}
    CondVar& getCondVar() {return m_condVar;}

  private:
    Selector m_selector;
    CondVar m_condVar;
    Thread* m_thread;
    bool m_running;
    std::list<TcpSocket*>* m_socketList;
  };  
}; // namespace mognetwork

#endif // !TCPASIOWRITER_HH_
