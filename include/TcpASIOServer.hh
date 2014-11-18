//
// TcpASIOServer.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Sat Nov 15 18:00:03 2014 Moghrabi Alexandre
// Last update Tue Nov 18 13:12:27 2014 Moghrabi Alexandre
//

/*!
 * \file TcpASIOServer.hh
 * \brief Gère les threads d'écriture et de lecture
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_TCPASIOSERVER_HH
# define MOGNETWORK_TCPASIOSERVER_HH

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

  public:
    /*!
     * \brief Récupère le writer TcpASIOWriter
     * \return un pointeur sur le TcpASIOWriter
     */
    TcpASIOWriter* getServerWriter() const {return m_serverWriter;}
    /*!
     * \brief Récupère le listener TcpASIOListener
     * \return un pointeur sur le TcpASIOWriter
     */
    TcpASIOListener* getServerListener() const {return m_serverListener;}

  private:
    TcpASIOListener* m_serverListener; /*!< instance du thread d'écoute */
    TcpServerSocket m_serverSocket; /*!< socket serveur */
    TcpASIOWriter* m_serverWriter; /*!< instance du thread d'écriture */
    int m_port; /*!< port d'écoute du serveur */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_TCPASIOSERVER_HH
