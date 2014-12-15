//
// Selector.hh for mognetwork in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Wed Jun 11 15:43:12 2014 mognetworkhrabi Alexandre
// Last update Mon Dec 15 07:44:24 2014 Moghrabi Alexandre
//

/*!
 * \file Selector.hh
 * \brief Select encapsulation
 * \author AlexMog
 * \version 0.1
 * \depreciated Untested
 */

#ifndef MOGNETWORK_SELECTOR_HH
# define MOGNETWORK_SELECTOR_HH

#ifndef OS_WINDOWS
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#endif // !OS_WINDOWS
#include <sys/types.h>
#include <list>
#include "SocketFD.hh"

typedef timeval Time; /*!< Time val typedef (yup, i like it) */

namespace mognetwork
{
  /*!
   * \class Selector
   * \brief Select encapsulation
   */
  class Selector
  {
  public:
    /*!
     * \enum State
     * \brief Defines the states of the select
     */
    enum State
      {
	Waiting,
	Error
      };
    /*!
     * \brief Default constructor
     */
    Selector();
    virtual ~Selector();
    
  public:
    /*!
     * \brief Wait for a new update of the Selector
     */
    void waitForTrigger();
    
  public:
    /*!
     * \brief Get the timeout value
     * \return The timeout value
     */
    Time* getTimeout() const {return m_timeout;}
    /*!
     * \brief Get the actual state of the Selector
     * \return State of the Selector
     */
    State getState() const {return m_state;}
    /*!
     * \brief Get the socket list that are ready to be edited in writing mode
     * \reutn The list of the SocketFD
     */
    const std::list<SocketFD>& getWritingTriggeredSockets() const {return m_writeUpdated;}
    /*!
     * \brief Get the socket list that are ready to be readed
     * \return List of the SocketFD
     */
    const std::list<SocketFD>& getReadingTriggeredSockets() const {return m_readUpdated;}
    
  public:
    /*!
     * \brief Defines a value for the timeout
     * \param timeout the timeout value
     */
    void setTimeout(Time* timeout) {m_timeout = timeout;}
    /*!
     * \brief Add a fd to the writing trigger
     * \param fd the SocketFD to add
     */
    void addFdToWrite(SocketFD fd);
    /*!
     * \brief Add a fd to the reading trigger
     * \param fd the SocketFD to add
     */
    void addFdToRead(SocketFD fd);
    /*!
     * \brief Delete a fd from the writing trigger
     * \param fd the SocketFD to remove
     */
    void remFdToWrite(SocketFD fd) {m_writeSockets.remove(fd);}
    /*!
     * \brief Delete a fd from the reading trigger
     * \param fd the SocketFD to remove
     */
    void remFdToRead(SocketFD fd) {m_readSockets.remove(fd);}
    void clearFdToWrite() {m_writeSockets.clear();}
    void clearFdToRead() {m_readSockets.clear();}
    
  private:
    /*!
     * \brief Initialize the state Fds
     */
    void setFds();
    /*!
     * \brief Update the Fds
     */
    void updateFds();
    
  private:
    Time* m_timeout; /*!< Select Timeout */
    std::list<SocketFD> m_readSockets; /*!< Fd list to be monitored on reading */
    std::list<SocketFD> m_writeSockets; /*!< Fd list to be monitored on writing */
    std::list<SocketFD> m_readUpdated; /*!< Fd list of the triggered reading sockets */
    std::list<SocketFD> m_writeUpdated; /*!< Fd list of the triggered writing sockets */
    State m_state; /*!< Selector state */
    fd_set m_rdfs; /*!< Fd reading set */
    fd_set m_wdfs; /*!< Fd writing set */
    int m_maxFds; /*!< FD max for the select */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_SELECTOR_HH
