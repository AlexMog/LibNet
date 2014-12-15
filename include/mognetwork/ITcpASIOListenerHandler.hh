//
// ITcpASIOListenerHandler.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 00:44:56 2014 Moghrabi Alexandre
// Last update Mon Dec 15 09:43:51 2014 Moghrabi Alexandre
//

/*!
 * \file ITcpASIOListenerHandler.hh
 * \brief Handler for the TcpASIOListener
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
   * \brief Handler for the TcpASIOListener
   */
  class ITcpASIOListenerHandler
  {
  public:
    virtual ~ITcpASIOListenerHandler() {}
    /*!
     * \brief Called when a new client is connected
     * \param client the connected client
     */
    virtual void onConnect(TcpSocket& client) = 0;
    /*!
     * \brief Called when a client send datas, and the datas are fully readed
     * \param client the client who sended the datas
     */
    virtual void onReceivedData(TcpSocket& client) = 0;
    /*!
     * \brief Called when a client disconnects
     * \param client the disconnected client
     */
    virtual void onDisconnect(TcpSocket& client) = 0;
  };
} // namespace mognetwork

#endif // !MOGNETWORK_ITCPASIOLISTENERHANDLER_HH
