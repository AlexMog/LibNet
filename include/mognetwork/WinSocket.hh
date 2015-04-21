//
// WinSocket.hh for WinSocket in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:43:05 2014 mognetworkhrabi Alexandre
// Last update Tue Apr 21 10:36:58 2015 Moghrabi Alexandre
//

/*!
 * \file WinSocket.hh
 * \brief Windows Socket
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_WINSOCKET_HH
# define MOGNETWORK_WINSOCKET_HH

#ifdef _WIN32_WINDOWS
  #undef _WIN32_WINDOWS
#endif
#ifdef _WIN32_WINNT
  #undef _WIN32_WINNT
#endif
#define _WIN32_WINDOWS 0x0501
#define _WIN32_WINNT 0x0501
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include "SocketFD.hh"
#include "Socket.hh"

/*!
 * \namespace mognetwork
 * namespace used for the libnet classes
 */
namespace mognetwork
{
  /*!
   * \class OsSocket
   * \brief Implementation of the windows sockets
   */
class OsSocket
{
public:
  typedef int AddreLength; /*!< length of an address */
  /*!
   * \brief create a sockaddr_in
   * \param address : the address in Uint32
   * \param port : the port to use
   * \return sockaddr_in the initialised structure
   */
  static sockaddr_in createAddress(UINT32 address, unsigned short port);
  /*!
   * \brief Get the socket state of an unvalid socket
   * \return SocketFD a unvalid fd
   */
  static SocketFD notValid();
  /*!
   * \brief Close the socket
   * \param socket the SocketFD to close
   */
  static void close(SocketFD socket);
  /*!
   * \brief Get the error status of the socket
   * \return Socket::Status the status of the socket
   */
  static Socket::Status getErrorStatus();
};
} // namespace mognetwork

#endif // !MOGNETWORK_WINSOCKET_HH
