//
// TcpASIOWriter.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 17:35:53 2014 Moghrabi Alexandre
// Last update Wed Nov 12 19:30:52 2014 Moghrabi Alexandre
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
  class TcpASIOWriter
  {
  public:
    TcpASIOWriter(const TcpSocket& serverSocket);
    virtual ~TcpASIOWriter();

  public:
    void start();
    void stop();
    void wait();

  private:
    void setFds();

  public:
    bool isRunning() const {return m_runner->m_running;}

  private:
    TcpSocket* getSocketByFd(SocketFD fd);
    Selector& getSelector() {return m_selector;}
    CondVar& getCondVar() {return m_condVar;}

  private:
    class Runner : public IRunnable
    {
    public:
      Runner(TcpASIOWriter& parent) : m_running(true), m_parent(parent) {}
      virtual ~Runner() {}
      void run();

    public:
      bool m_running;

    private:
      TcpASIOWriter& m_parent;
    };

  private:
    const TcpSocket& m_serverSocket;
    Selector m_selector;
    CondVar m_condVar;
    Thread* m_thread;
    Runner* m_runner;
    std::list<TcpSocket*>* m_socketList;
  };  
}; // namespace mognetwork

#endif // !TCPASIOWRITER_HH_
