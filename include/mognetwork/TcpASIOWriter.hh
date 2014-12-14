//
// TcpASIOWriter.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 17:35:53 2014 Moghrabi Alexandre
// Last update Sat Dec 13 05:12:24 2014 Moghrabi Alexandre
//

/*!
 * \file TcpASIOWriter.hh
 * \brief Thread d'écriture des sockets en ASIO
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_TCPASIOWRITER_HH
# define MOGNETWORK_TCPASIOWRITER_HH

# include "TcpSocket.hh"
# include "SocketFD.hh"
# include "Selector.hh"
# include "CondVar.hh"
# include "Thread.hh"
# include "IRunnable.hh"
# include <list>

namespace mognetwork
{
  /*!
   * \class TcpASIOWriter
   * \brief Thread d'écriture des sockets en ASIO
   */
  class TcpASIOWriter : private IRunnable
  {
  public:
    /*!
     * \brief Constructeur par défaut.
     */
    TcpASIOWriter();
    virtual ~TcpASIOWriter();

  public:
    /*!
     * \brief démarre le thread d'écriture.
     */
    void start();
    /*!
     * \brief arrête le thread d'écriture.
     */
    void stop();
    /*!
     * \brief Attends que le thread termine son exécution
     */
    void wait();
    /*!
     * \brief A utiliser lors de l'envois de données sur une ou plusieurs sockets.
     */
    void triggerData() {m_condVar.signal();}

  private:
    void setFds();

  public:
    /*!
     * \brief Permet de connaitre l'état du thread
     * \return true si le thread d'écriture est lancé
     */
    bool isRunning() const {return m_running;}

  public:
    /*!
     * \brief Utilisé pour le thread
     */
    void run();

  public:
    /*!
     * \brief Permet de récupérer le selector utilisé.
     * \return une référence sur le Selector utilisé par le thread.
     */
    Selector& getSelector() {return m_selector;}
    /*!
     * \brief Permet de récupérer la condVar utilisée par le thread.
     * \return une référence sur le CondVar utilisé par le thread.
     */
    CondVar& getCondVar() {return m_condVar;}

  private:
    Selector m_selector; /*!< Selector utilisé par le thread */
    CondVar m_condVar; /*!< CondVar utilisée par le thread */
    Thread* m_thread; /*!< Thread instance */
    bool m_running; /*!< etat du thread */
    std::list<TcpSocket*>* m_socketList; /*!< Liste des sockets pour éviter un surplus d'appel au singleton */
    Time m_timeout;
  };  
} // namespace mognetwork

#endif // !MOGNETWORK_TCPASIOWRITER_HH
