//
// ITcpASIOListenerHandler.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 00:44:56 2014 Moghrabi Alexandre
// Last update Thu Nov 13 12:45:34 2014 Moghrabi Alexandre
//

/*!
 * \file ITcpASIOListenerHandler.hh
 * \brief Handler pour le TcpASIOListener
 * \author AlexMog
 * \version 0.1
 */

#ifndef ITCPASIOLISTENERHANDLER_HH_
# define ITCPASIOLISTENERHANDLER_HH_

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
}; // namespace mognetwork

#endif // !ITCPASIOLISTENERHANDLER_HH_
