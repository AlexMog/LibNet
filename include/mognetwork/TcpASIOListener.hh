//
// TcpASIOListener.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Nov 10 18:10:20 2014 Moghrabi Alexandre
// Last update Wed Mar 25 16:01:58 2015 Moghrabi Alexandre
//

/*!
 * \file TcpASIOListener.hh
 * \brief Listen and read datas in ASIO mode.
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_TCPASIOLISTENER_HH
# define MOGNETWORK_TCPASIOLISTENER_HH

# include <list>
# include "mognetwork/OS.hh"
#ifndef OS_WINDOWS
# include <unistd.h>
#endif // !OS_WINDOWS
# include "IRunnable.hh"
# include "Thread.hh"
# include "TcpServerSocket.hh"
# include "Selector.hh"
# include "ITcpASIOListenerHandler.hh"

namespace mognetwork
{
  class TcpASIOServer;
  /*!
   * \class TcpASIOListener
   * \brief Listen and read datas in ASIO mode.
   */
  class TcpASIOListener : private IRunnable
  {
  public:
    /*!
     * \brief default constructor
     * \param serverSocket The server socket to be used. (must be connected)
     */
    TcpASIOListener(TcpServerSocket& serverSocket);
    /*!
     * \brief default constructor
     * \param serverSocket The server socket to be used. (must be connected)
     * \param server Used by TcpASIOServer
     */
    TcpASIOListener(TcpASIOServer* server);
    virtual ~TcpASIOListener();

  public:
    /*!
     * \brief Start the listening thread
     */
    void start();
    /*!
     * \brief Stop the listening thread
     */
    void stop();
    /*!
     * \brief Wait until the end of the listening thread
     */
    void wait();

  public:
    /*!
     * \brief Add a ITcpASIOListenerHandler to the thread
     * \param listener the listener to add
     */
    void addListener(ITcpASIOListenerHandler* listener) {m_listeners.push_back(listener);}

  public:
    /*!
     * \brief Know if the listener is running
     * \return true if it is listening, false if not
     */
    bool isRunning() const {return m_running;}

  public:
    /*!
     * \brief Used by the thread. See IRunnable.
     */
    void run();

  private:
    void acceptClient();
    void init();

  public:
    /*!
     * \brief Get the Selector used.
     * \return The Selector reference.
     */
    Selector& getSelector() {return m_selector;}

  private:
    bool m_running; /*!< state of the Thread */
    std::list<ITcpASIOListenerHandler*> m_listeners; /*!< list of the listeners */
    Selector m_selector; /*!< the Selector used */
    Thread* m_thread; /*!< Thread instance */
    std::list<TcpSocket*>* m_socketList; /*!< A pointer on the list, used to not call too many times the Singleton */
    Mutex* m_mutex;
    int m_pipefd[2]; /*!< pipe used to stop the listener */
    TcpServerSocket& m_serverSocket; /*!< reference on the TcpServerSocket */
    Time m_timeout; /* Timeout value for the select */
    TcpASIOServer* m_server;
  };
} // namespace mognetwork

#endif // !MOGNETWORK_TCPASIOLISTENER_HH
