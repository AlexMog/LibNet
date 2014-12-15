//
// TcpASIOWriter.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 17:35:53 2014 Moghrabi Alexandre
// Last update Mon Dec 15 07:24:42 2014 Moghrabi Alexandre
//

/*!
 * \file TcpASIOWriter.hh
 * \brief Writing Thread for the TcpASIOServer
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_TCPASIOWRITER_HH
# define MOGNETWORK_TCPASIOWRITER_HH

# include "TcpSocket.hh"
# include "SocketFD.hh"
# include "Selector.hh"
# include "CondVar.hh"
# include "Thread.hh"
# include "IRunnable.hh"
# include <list>

namespace mognetwork
{
  /*!
   * \class TcpASIOWriter
   * \brief Writing Thread for the TcpASIOServer
   */
  class TcpASIOWriter : private IRunnable
  {
  public:
    /*!
     * \brief Default constructor
     */
    TcpASIOWriter();
    virtual ~TcpASIOWriter();

  public:
    /*!
     * \brief Start the thread
     */
    void start();
    /*!
     * \brief Stop the thread
     */
    void stop();
    /*!
     * \brief Wait for the thread to end
     */
    void wait();
    /*!
     * \brief Used to tell to the thread that there is datas waiting to be sended!
     */
    void triggerData() {m_condVar.signal();}

  private:
    void setFds();

  public:
    /*!
     * \brief Know the state of the writer
     * \return true if the it is running
     */
    bool isRunning() const {return m_running;}

  public:
    /*!
     * \brief Used for the thread
     */
    void run();

  public:
    /*!
     * \brief Used to get the Selector used
     * \return a reference on the Selector
     */
    Selector& getSelector() {return m_selector;}
    /*!
     * \brief Used to get the CondVar used
     * \return a reference on the CondVar
     */
    CondVar& getCondVar() {return m_condVar;}

  private:
    Selector m_selector; /*!< The Selector used */
    CondVar m_condVar; /*!< The CondVar used */
    Thread* m_thread; /*!< The Thread instance */
    bool m_running; /*!< The writing state */
    std::list<TcpSocket*>* m_socketList; /*!< A list of sockets to limit the singleton usage */
    Time m_timeout;
  };  
} // namespace mognetwork

#endif // !MOGNETWORK_TCPASIOWRITER_HH
