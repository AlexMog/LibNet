//
// Socket.hh for Network in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:07:37 2014 mognetworkhrabi Alexandre
// Last update Mon Dec 15 07:38:20 2014 Moghrabi Alexandre
//

/*!
 * \file Socket.hh
 * \brief Socket base, used to defines sockets and instanciate sockets (Udp, Tcp)
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_SOCKET_HH
#define MOGNETWORK_SOCKET_HH

#include "SocketFD.hh"

namespace mognetwork
{
  /*!
   * \class Socket
   * \brief Socket base, used to define sockets and instanciate sockets (Udp, Tcp)
   */
  class Socket
  {
  public:
    /*!
     * \enum Status
     * \brief The possible status of the socket
     */
    enum Status
      {
	Ok, /*!< Socket ready for reading/writing */
	Nok, /*!< Socket not ready */
	Disconnected, /*!< Socket disconnected */
	Waiting, /*!< Socket waiting for datas */
	Error /*!< Unknow error */
      };
    
  public:
    virtual ~Socket();
    /*!
     * \brief Get the SocketFD of a socket
     * \return the file descriptor of the socket
     */
    SocketFD getSocketFD() const;
    
  protected:
    /*!
     * \enum Type
     * \brief Defines the socket type
     */
    enum Type
      {
	Tcp, /*!< TCP */
	Udp /*!< UDP */
      };
    /*!
     * \brief Default constructor
     * \param type The socket type to use
     */
    Socket(Type type);
    /*!
     * \brief Create the socket and instanciate a SocketFD
     */
    void create();
    /*!
     * \brief Create the socket while using an opened SocketFD
     */
    void create(SocketFD fd);
    /*!
     * \brief Close the socket
     */
    void close();
    
  private:
    Type m_type; /*!< Type of the socket */
    SocketFD m_socket; /*!< File descriptor of the socket */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_SOCKET_HH
