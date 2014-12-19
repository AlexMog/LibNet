//
// TcpASIODatas.hh for LibNEt in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 18:28:09 2014 Moghrabi Alexandre
// Last update Fri Dec 19 08:18:26 2014 Moghrabi Alexandre
//

/*!
 * \file TcpASIODatas.hh
 * \brief Used to send datas between the threads. Is a Singleton.
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_TCPASIODATAS_HH
# define MOGNETWORK_TCPASIODATAS_HH

# include <list>
# include "TcpSocket.hh"
# include "Singleton.hh"
# include "Mutex.hh"

namespace mognetwork
{
  /*!
   * \class TcpASIODatas
   * \brief Used to send datas between the threads. Is a Singleton.
   */
  class TcpASIODatas
  {
  public:
    /*!
     * \brief Get the instance of the Singleton.
     * \return the instance
     */
    static TcpASIODatas* getInstance() {return (&Singleton<TcpASIODatas>::Instance());}
    virtual ~TcpASIODatas();

  public:
    /*!
     * \depreciated Used only by the Singleton. DO NOT USE.
     */
    TcpASIODatas();

  public:
    /*!
     * \brief Get the partaged mutex
     * \return The partaged mutex
     */
    Mutex& getMutex() {return m_mutex;}
    /*!
     * \brief Get a TcpSocket via his SocketFD
     * \param fd The SocketFD to find
     * \return the TcpSocket found
     */
    TcpSocket* getSocketByFd(SocketFD fd);
    /*!
     * \brief Get the TcpSocket list
     * \return The TcpSocket list
     */
    std::list<TcpSocket*>* getSocketList() const {return m_socketList;}

  public:
    /*!
     * \brief Add a socket to the list
     * \param socket a pointer on the TcpSocket to add
     */
    void addSocket(TcpSocket* socket) {m_socketList->push_back(socket);}
    /*!
     * \brief Delete an existing socket
     * \param socket the address of the TcpSocket to remove.
     */
    void remSocket(TcpSocket* socket) {m_socketList->remove(socket);}
    /*!
     * \brief Delete an existing socket
     * \param socket the SocketFD of the existing socket.
     */
    void remSocket(SocketFD socket);

  private:
    std::list<TcpSocket*>* m_socketList; /*!< List of the sockets connected */
    Mutex m_mutex;
  };
} // namespace mognetwork

#endif // !MOGNETWORK_TCPASIODATAS_HH
