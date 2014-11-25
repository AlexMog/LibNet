//
// TcpASIOListener.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Nov 10 18:10:20 2014 Moghrabi Alexandre
// Last update Tue Nov 18 13:12:34 2014 Moghrabi Alexandre
//

/*!
 * \file TcpASIOListener.hh
 * \brief Permet la gestion de la lecture de données en ASIO
 * \author AlexMog
 * \version 0.1
 * \depreciated non terminé
 */

#ifndef MOGNETWORK_TCPASIOLISTENER_HH
# define MOGNETWORK_TCPASIOLISTENER_HH

# include <list>
# include <unistd.h>
# include "IRunnable.hh"
# include "Thread.hh"
# include "TcpServerSocket.hh"
# include "Selector.hh"
# include "ITcpASIOListenerHandler.hh"

namespace mognetwork
{
  /*!
   * \class TcpASIOListener
   * \brief Permet la gestion de la lecture de données en ASIO
   */
  class TcpASIOListener : private IRunnable
  {
  public:
    /*!
     * \brief constructeur par défaut
     * \param serverSocket la socket serveur
     */
    TcpASIOListener(TcpServerSocket& serverSocket);
    virtual ~TcpASIOListener();

  public:
    /*!
     * \brief Démarre le thread d'écoute
     */
    void start();
    /*!
     * \brief Arrête le thread d'écoute
     */
    void stop();
    /*!
     * \brief Permet d'attendre la fin de l'exécution du thread d'écoute
     */
    void wait();

  public:
    /*!
     * \brief Ajoute un listener au thread d'écoute
     * \param listener le listener à ajouter, instance de ITCpASIOListenerHandler
     */
    void addListener(ITcpASIOListenerHandler* listener) {m_listeners.push_back(listener);}

  public:
    /*!
     * \brief Permet de savoir si le thread est démarré
     * \return true si démarré, false sinon
     */
    bool isRunning() const {return m_running;}

  public:
    /*!
     * \brief Utilisé par le thread. IRunnable.
     */
    void run();

  private:
    void acceptClient();

  public:
    /*!
     * \brief Permet de récupérer une référence sur le selector du thread
     * \return la référence sur le Selector
     */
    Selector& getSelector() {return m_selector;}

  private:
    bool m_running; /*!< etat du thread */
    std::list<ITcpASIOListenerHandler*> m_listeners; /*!< liste des listeners */
    Selector m_selector; /*!< le selector du thread */
    Thread* m_thread; /*!< l'instance du thread */
    std::list<TcpSocket*>* m_socketList; /*!< un pointeur sur la liste des sockets stockée par TcpASIODatas */
    int m_pipefd[2]; /*!< un pipe pour déclancher le Selector en cas de besoins */
    TcpServerSocket& m_serverSocket; /*!< une référence sur la socket serveur */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_TCPASIOLISTENER_HH
