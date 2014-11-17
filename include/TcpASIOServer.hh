//
// TcpASIOServer.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Sat Nov 15 18:00:03 2014 Moghrabi Alexandre
// Last update Mon Nov 17 18:41:45 2014 Moghrabi Alexandre
//

/*!
 * \file TcpASIOServer.hh
 * \brief Gère les threads d'écriture et de lecture
 * \author AlexMog
 * \version 0.1
 */

#ifndef TCPASIOSERVER_HH_
# define TCPASIOSERVER_HH_

# include <list>
# include "TcpServerSocket.hh"
# include "TcpASIOListener.hh"
# include "TcpASIOWriter.hh"

namespace mognetwork
{
  /*!
   * \class TcpASIOServer
   * \brief Gère les threads d'écriture et de lecture en ASIO
   */
  class TcpASIOServer
  {
  public:
    /*!
     * \brief Constructeur par défaut
     * \param port Le port sur lequel le serveur écoute
     */
    TcpASIOServer(int port);
    virtual ~TcpASIOServer();

  public:
    /*!
     * \brief Démarre les différents threads, et attends qu'ils se terminent.
     */
    void start();
    /*!
     * \brief Arrête le thread de lecture et d'écriture.
     */
    void stop();
    /*!
     * \brief Ajoute un listener au serveur.
     * \param listener le listener en question en utilisant ITcpASIOListenerHandler
     */
    void addListener(ITcpASIOListenerHandler* listener) {m_serverListener->addListener(listener);}
    /*!
     * \brief Dans le cas ou une socket client contient des données à envoyer, met à jour le thread d'écriture
     */
    void sendPendingDatas() {m_serverWriter->triggerData();}

  private:
    TcpASIOListener* m_serverListener; /*!< instance du thread d'écoute */
    TcpServerSocket m_serverSocket; /*!< socket serveur */
    TcpASIOWriter* m_serverWriter; /*!< instance du thread d'écriture */
    int m_port; /*!< port d'écoute du serveur */
  };
}; // namespace mognetwork

#endif // !TCPASIOSERVER_HH_
