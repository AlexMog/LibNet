//
// ITcpASIOListenerHandler.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 00:44:56 2014 Moghrabi Alexandre
// Last update Tue Nov 18 13:37:29 2014 Moghrabi Alexandre
//

/*!
 * \file ITcpASIOListenerHandler.hh
 * \brief Handler pour le TcpASIOListener
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_ITCPASIOLISTENERHANDLER_HH
# define MOGNETWORK_ITCPASIOLISTENERHANDLER_HH

# include "TcpSocket.hh"

namespace mognetwork
{
  /*!
   * \class ITcpASIOListernerHandler
   * \brief Handler pour le TcpASIOListener
   */
  class ITcpASIOListenerHandler
  {
  public:
    virtual ~ITcpASIOListenerHandler() {}
    /*!
     * \brief Appelé lors de la connexion d'un nouveau client
     * \param client le client qui c'est connecté
     */
    virtual void onConnect(TcpSocket& client) = 0;
    /*!
     * \brief Appelé lors de la réception totale d'une donnée
     * \param client le client qui a trigger les données
     */
    virtual void onReceivedData(TcpSocket& client) = 0;
    /*!
     * \brief Appelé lors de la déconnexion d'un client
     * \param client le client qui c'est déconnecté
     */
    virtual void onDisconnect(TcpSocket& client) = 0;
  };
} // namespace mognetwork

#endif // !MOGNETWORK_ITCPASIOLISTENERHANDLER_HH
