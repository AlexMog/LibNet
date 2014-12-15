//
// TcpServerSocket.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Nov 17 17:41:35 2014 Moghrabi Alexandre
// Last update Mon Dec 15 07:20:39 2014 Moghrabi Alexandre
//

/*!
 * \file TcpServerSocket.hh
 * \brief Socket pour la gestion simplifiée du serveur
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_TCPSERVERSOCKET_HH
# define MOGNETWORK_TCPSERVERSOCKET_HH

# include "IpAddress.hh"
# include "TcpSocket.hh"

namespace mognetwork
{
  /*!
   * \class TcpServerSocket
   * \brief Socket to simplify the server usage
   */
  class TcpServerSocket : public TcpSocket
  {
  public:
    /*!
     * \brief default constructor
     */
    TcpServerSocket();
    virtual ~TcpServerSocket();

  public:
    /*!
     * \brief Accept a new client connexion
     * \return a pointer on a new instance of a TcpSocket
     */
    TcpSocket* accept();
    /*!
     * \brief Bind the socket on a port
     * \param port the port to bind on
     */
    void bind(int port);
    /*!
     * \brief Listen on the socket
     * \param maxWaitingList the waiting request queue
     */
    void listen(int maxWaitingList);

  public:
    /*!
     * \brief Used to know of a socket is binded
     * \return true if binded
     */
    bool isBound() const {return m_bound;}
    /*!
     * \brief Used to know if the socket is actually listening
     * \ return true if it is listening
     */
    bool isListening() const {return m_listening;}

  private:
    bool m_bound; /*!< Bind state */
    bool m_listening; /*!< Listening state */
    int m_port; /*!< Port */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_TCPSERVERSOCKET_HH
