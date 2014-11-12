//
// Selector.hh for mognetwork in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Wed Jun 11 15:43:12 2014 mognetworkhrabi Alexandre
// Last update Wed Nov 12 19:28:11 2014 Moghrabi Alexandre
//

/*!
 * \file Selector.hh
 * \brief Encapsulation du Select
 * \author AlexMog
 * \version 0.1
 * \depreciated Untested
 */

#ifndef SELECTOR_HH
# define SELECTOR_HH

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <list>
#include "SocketFD.hh"

typedef timeval Time; /*!< Time val typedef (yup, i like it) */

namespace mognetwork
{
  /*!
   * \class Selector
   * \brief Encapsulation du select
   */
  class Selector
  {
  public:
    /*!
     * \enum State
     * \brief Enum définissant les différents états du select
     */
    enum State
      {
	Waiting,
	Error
      };
    /*!
     * \brief Constructeur du select
     */
    Selector();
    ~Selector();
    
  public:
    /*!
     * \brief Attends que le select saute
     */
    void waitForTrigger();
    
  public:
    /*!
     * \brief Récupère le timeout
     * \return Le timeout via une structure timeval
     */
    Time* getTimeout() const {return m_timeout;}
    /*!
     * \brief Récupère l'état actuel du select
     * \return L'état du select
     */
    State getState() const {return m_state;}
    /*!
     * \brief Récupère les sockets qui sont modifiables en écriture
     * \reutn Liste contenant les sockets modifiables
     */
    const std::list<SocketFD>& getWritingTriggeredSockets() const {return m_writeUpdated;}
    /*!
     * \brief Récupère les sockets qui ont été modifiées en lecture
     * \return Liste contenant les sockets modifiées
     */
    const std::list<SocketFD>& getReadingTriggeredSockets() const {return m_readUpdated;}
    
  public:
    /*!
     * \brief Définit une valeur pour le timeout
     * \param timeout le timeout en question
     */
    void setTimeout(Time* timeout) {m_timeout = timeout;}
    /*!
     * \brief Ajoute un fd à la surveillance sur l'écriture
     * \param fd le FD à ajouter
     */
    void addFdToWrite(SocketFD fd);
    /*!
     * \brief Ajoute un fd à la surveillance en lecture
     * \param fd le FD à ajouter
     */
    void addFdToRead(SocketFD fd);
    /*!
     * \brief Supprime un fd à la surveillance en écriture
     * \param fd le socket à supprimer
     */
    void remFdToWrite(SocketFD fd) {m_writeSockets.remove(fd);}
    /*!
     * \brief supprime un fd à la surveillance en écriture
     * \param fd le socket à supprimer
     */
    void remFdToRead(SocketFD fd) {m_readSockets.remove(fd);}
    void clearFdToWrite() {m_writeSockets.clear();}
    void clearFdToRead() {m_readSockets.clear();}
    
  private:
    /*!
     * \brief Définit l'état des fd
     */
    void setFds();
    /*!
     * \brief Modifie l'état des fd
     */
    void updateFds();
    
  private:
    Time* m_timeout; /*!< Timeout du select */
    std::list<SocketFD> m_readSockets; /*!< Liste des fd à monitorer en lecture */
    std::list<SocketFD> m_writeSockets; /*!< Liste des fd à monitorer en écriture */
    std::list<SocketFD> m_readUpdated; /*!< Liste des fd modifiés en lecture */
    std::list<SocketFD> m_writeUpdated; /*!< Liste des fd pouvant être modifiés en écriture */
    State m_state; /*!< Etat du select */
    fd_set m_rdfs; /*!< Liste des fd en lecture */
    fd_set m_wdfs; /*!< Liste des fd en écriture */
    int m_maxFds; /*!< FD max pour le select */
  };
}; // namespace mognetwork

#endif // !SELECTOR_HH
