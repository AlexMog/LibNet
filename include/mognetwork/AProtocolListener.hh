//
// AProtocolListener.hh for ProtocolListener in /home/alexmog/projets/LibNet/include/mognetwork
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 15:05:31 2015 Moghrabi Alexandre
// Last update Tue Apr 28 10:59:56 2015 Moghrabi Alexandre
//

/*!
 * \file AProtocolListener.hh
 * \brief The protocol Abstract class
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_APROTOCOLLISTENER_HH
# define MOGNETWORK_APROTOCOLLISTENER_HH

# include "TcpSocket.hh"

namespace mognetwork
{
  /*!
   * \namespace protocol
   * namespace used for the protocols
   */
  namespace protocol
  {
    /*!
     * \class AProtocolListener
     * \brief Used to create a new protocol
     */
    class AProtocolListener
    {
    public:
      AProtocolListener(TcpSocket* socket);
      virtual ~AProtocolListener();
      
    public:
      /*!
       * \biref Called when a socket has datas to be readed
       * \return The connection status
       */
      virtual Socket::Status onReadTrigger() = 0;
      /*!
       * \brief Used to know if the pendingDatas are ready
       * \return True if the pendingDatas are complete
       */
      virtual bool datasFullyReceived() = 0;
      /*!
       * \brief Called when datas are added to the send list.
       * \param data The datas to be send
       * \param size The size of the datas to send
       * \param dataToSend a std::vector<char> will be sended after this call
       */
      virtual void onSendDatas(const char* data, std::size_t size, TcpSocket::Data& dataToSend) = 0;
      /*!
       * \brief Called when the function "ReadAll" (blocking) is called
       * \param data The datas to be send
       * \return The connection status
       */
      virtual Socket::Status onReadAllTrigger(TcpSocket::Data& data) = 0;
      /*!
       * \brief Used to get the readedDatas when they are completed.
       * \return The readed datas
       */
      virtual TcpSocket::ReadedDatas& getReadedDatas();
      /*!
       * \brief Flush the pending datas reader.
       */
      virtual void flushReader();
      
    protected:
      TcpSocket* m_socket;
      TcpSocket::ReadedDatas m_pendingDatas;
    };
  }
}
#endif /* !MOGNETWORK_APROTOCOLLISTENER_HH */
