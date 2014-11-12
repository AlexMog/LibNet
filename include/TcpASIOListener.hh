//
// TcpASIOListener.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Nov 10 18:10:20 2014 Moghrabi Alexandre
// Last update Wed Nov 12 17:45:10 2014 Moghrabi Alexandre
//

/*!
 * \file TcpASIOListener.hh
 * \brief Permet la gestion de la lecture de données en ASIO
 * \author AlexMog
 * \version 0.1
 * \depreciated non terminé
 */

#ifndef TCPASIOLISTENER_HH_
# define TCPASIOLISTENER_HH_

# include "TcpSocket.hh"
# include "ITcpASIOListenerHandler.hh"

namespace mognetwork
{
  class TcpASIOListener
  {
  public:
    TcpASIOListener(const TcpSocket& serverSocket, const ITcpASIOListenerHandler& handler);
    virtual ~TcpASIOListener();

  public:
    void init();
    void start();
    void stop();

  private:
    const TcpSocket& m_serverSocket;
    const ITcpASIOListenerHandler& m_handler;
  };
}; // namespace mognetwork

#endif // !TCPASIOLISTENER_HH_
