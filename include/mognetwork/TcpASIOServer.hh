//
// TcpASIOServer.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Sat Nov 15 18:00:03 2014 Moghrabi Alexandre
// Last update Mon Dec 15 07:27:42 2014 Moghrabi Alexandre
//

/*!
 * \file TcpASIOServer.hh
 * \brief Gère les threads d'écriture et de lecture
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_TCPASIOSERVER_HH
# define MOGNETWORK_TCPASIOSERVER_HH

# include <list>
# include "TcpServerSocket.hh"
# include "TcpASIOListener.hh"
# include "TcpASIOWriter.hh"

namespace mognetwork
{
  /*!
   * \class TcpASIOServer
   * \brief Used to create a ASIO Server simply
   */
  class TcpASIOServer
  {
  public:
    /*!
     * \brief Default constructor
     * \param port The port to be used with the server
     */
    TcpASIOServer(int port);
    virtual ~TcpASIOServer();

  public:
    /*!
     * \brief Start the threads and wait until they are stopped
     */
    void start();
    /*!
     * \brief Stop the threads
     */
    void stop();
    /*!
     * \brief Add a ITcpASIOListenerHandler to the server
     * \param listener the listener to add
     */
    void addListener(ITcpASIOListenerHandler* listener) {m_serverListener->addListener(listener);}
    /*!
     * \brief Tell the server that there is datas to send.
     */
    void sendPendingDatas() {m_serverWriter->triggerData();}

  public:
    /*!
     * \brief Get the TcpASIOWriter
     * \return a pointer on the TcpASIOWriter
     */
    TcpASIOWriter* getServerWriter() const {return m_serverWriter;}
    /*!
     * \brief Get the TcpASIOListener
     * \return a pointer on the TcpASIOListener
     */
    TcpASIOListener* getServerListener() const {return m_serverListener;}

  private:
    TcpASIOListener* m_serverListener; /*!< instance of the listening thread */
    TcpServerSocket m_serverSocket; /*!< server socket */
    TcpASIOWriter* m_serverWriter; /*!< instance of the writing thread */
    int m_port; /*!< listening port */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_TCPASIOSERVER_HH
