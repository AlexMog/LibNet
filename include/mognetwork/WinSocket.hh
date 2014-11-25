//
// WinSocket.hh for WinSocket in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:43:05 2014 mognetworkhrabi Alexandre
// Last update Tue Nov 18 13:07:29 2014 Moghrabi Alexandre
//

/*!
 * \file WinSocket.hh
 * \brief Socket windows
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
#include "SocketFD.hh"
#include "Socket.hh"
#include <winsock2.h>
#include <ws2tcpip.h>

/*!
 * \namespace mognetwork
 * espace de nommage des différents outils de la lib
 */
namespace mognetwork
{
  /*!
   * \class OsSocket
   * \brief Outils de socket générique de Windows
   */
class OsSocket
{
public:
  typedef int AddreLength; /*!< Typedef pour la longueur d'une adresse */
  /*!
   * \brief Crée un sockaddr_in
   * \param address : adresse en Uint32
   * \param port : le port à utiliser
   * \return sockaddr_in la structure initialisée
   */
  static sockaddr_in createAddress(Uint32 address, unsigned short port);
  /*!
   * \brief Vérifie si la socket est valide
   * \return SocketFD un fd valide
   */
  static SocketFD notValid();
  /*!
   * \brief Ferme la socket
   * \param socket le socketFD à partir duquel on crée la socket
   */
  static void close(SocketFD socket);
  /*!
   * \brief Vérifie le status de la socket
   * \return Socket::Status le status de la socket
   */
  static Socket::Status getErrorStatus();
};
} // namespace mognetwork

#endif // !MOGNETWORK_WINSOCKET_HH
