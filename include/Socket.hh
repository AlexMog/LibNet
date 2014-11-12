//
// Socket.hh for Network in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:07:37 2014 mognetworkhrabi Alexandre
// Last update Wed Nov 12 14:34:05 2014 Moghrabi Alexandre
//

/*!
 * \file Socket.hh
 * \brief Définit la base d'une socket
 * \author AlexMog
 * \version 1.0
 */

#ifndef SOCKET_HH
#define SOCKET_HH

#include "SocketFD.hh"

namespace mognetwork
{
  /*!
   * \class Socket
   * \brief Définit la base d'une socket
   */
  class Socket
  {
  public:
    /*!
     * \enum Status
     * \brief Définit les status possibles d'une socket
     */
    enum Status
      {
	Ok, /*!< Socket prête à la lecture/écriture */
	Nok, /*!< Socket non prête à la lecture/écriture */
	Disconnected, /*!< Socket déconnectée */
	Waiting, /*!< Attente de données */
	Error /*!< Erreur inconnue */
      };
    
  public:
    virtual ~Socket();
    /*!
     * \brief récupère le FD de la socket
     * \return le FD de la socket
     */
    SocketFD getSocketFD() const;
    
  protected:
    /*!
     * \enum Type
     * \brief Définit le type de socket
     */
    enum Type
      {
	Tcp, /*!< Socket TCP */
	Udp /*!< Socket UDP */
      };
    /*!
     * \brief Constructeur de la socket
     * \param type Le type de socket
     */
    Socket(Type type);
    /*!
     * \brief crée la socket et crée un FD
     */
    void create();
    /*!
     * \brief crée la socket via un FD déjà ouvert
     */
    void create(SocketFD fd);
    /*!
     * \brief ferme la socket
     */
    void close();
    
  private:
    Type m_type; /*!< Le type de socket */
    SocketFD m_socket; /*!< FD de la socket */
  };
} // namespace mognetwork

#endif /* !SOCKET_HH */
