//
// TcpSocket.hh for TCPSOCKET in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:59:35 2014 mognetworkhrabi Alexandre
// Last update Fri Feb 27 15:52:05 2015 Moghrabi Alexandre
//

/*!
 * \file TcpSocket.hh
 * \brief Gestion des sockets en TCP
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_TCPSOCKET_HH
# define MOGNETWORK_TCPSOCKET_HH

# include <list>
# include <vector>
# include <string>
# include "IpAddress.hh"
# include "Socket.hh"


namespace mognetwork
{
  class TcpASIOServer;
  class Packet;
  /*!
   * \class TcpSocket
   * \brief Used to create a Tcp Socket
   */
  class TcpSocket : public Socket
  {
  public:
    typedef std::vector<char> Data; /*!< Define data type */
    typedef std::list<Data*> DataList; /*!< Datas list */

  public:
    /*!
     * \brief Has all the datas to retrive and send process in ASIO
     */
    struct ReadedDatas
    {
      ReadedDatas(); /*!< Used to init the structure */
      std::size_t readed; /*!< Bytes readed */
      std::size_t totalSize; /*!< Total size to read */
      Data datas; /*!< Readed datas */
    };

    /*!
     * \brief Default constructor
     */
    TcpSocket();
    /*!
     * \brief Constructor used to define a TcpSocket with an actual opened FD.
     * \param fd The socket FD
     */
    TcpSocket(SocketFD fd);
    /*!
     * \brief Connects the socket to an address
     * \param address The IpAddress to connect on
     * \param port the port to connect the socket on
     */
    Socket::Status connect(const IpAddress& address, unsigned short port);
    /*!
     * \brief Disconnects the socket
     */
    void disconnect();
    /*!
     * \brief Send datas in sync mode.
     * \param data the datas to send (as a char array)
     * \param the size of the datas to send
     * \return Socket::Status state of the sended datas
     */
    Socket::Status send(const char* data, std::size_t size);
    /*!
     * \brief Receive datas in a defined mode
     * \param data a buffer to receive datas
     * \param size the size to read
     * \param received the received datas size
     * \param _flags the flags to use with recv
     * \return Socket::Status state connexion
     */
    Socket::Status receive(char* data, std::size_t size, std::size_t& received, int _flags);
    /*!
     * \brief Receive sync datas
     * \param data a Data object who is used as a buffer
     * \return Socket::Status connexion state
     */
    Socket::Status receiveAll(Data& data);
    /*!
     * \brief Add datas to async send list
     * \param data The datas to send (as a char array)
     * \param size Size of the datas to send
     * \return Socket::Status connexion state
     */
    Socket::Status asyncSend(const char* data, std::size_t size);
    /*!
     * \brief Send pending datas added with asyncSend
     * \return Socket::Status connexion state
     */
    Socket::Status sendPendingDatas();
    /*!
     * \brief Let you know if there is pending datas in the send list
     * \return true if there is data, false if not
     */
    bool havingPendingDatas() const;
    /*!
     * \brief Define datas that you can attach to the socket
     * \param userData the datas you want to attach to the socket
     */
    void setUserData(void* userData);
    /*!
     * \brief Get the userData you added to the socket
     * \return a pointer with the datas
     */
    void* getUserData() const;
    /*!
     * \brief Read waiting datas
     * \return Socket::Status connexion status
     */
    Socket::Status readPendingDatas();
    /*!
     * \brief Get datas that have been readed in async mode
     * \return The datas as TcpSocket::ReadedDatas
     */
    TcpSocket::ReadedDatas* getDatasReaded() const;
    /*!
     * \brief Get the readed datas as a Packet
     * \return Datas formatted with the Packet object
     */
    Packet* getPacketReaded();
    /*!
     * \brief Set the server when using TcpASIOServer
     * \param The TcpASIOServer pointer
     */
    void setServer(TcpASIOServer* server);
    /*!
     * \brief Get the TcpASIOServer parent of the socket
     * \return The TcpASIOServer pointer to the parent
     */
    TcpASIOServer* getServer() const;

  private:
    DataList m_pendingDatas; /*!< Waiting datas */
    ReadedDatas m_pendingRDatas; /*!< Waiting for read datas */
    ReadedDatas *m_allDataReaded; /*!< Readed datas */
    void* m_userData; /*!< Optional datas */
    TcpASIOServer* m_server;
  };
} // namespace mognetwork

#endif // !MOGNETWORK_TCPSOCKET_HH
