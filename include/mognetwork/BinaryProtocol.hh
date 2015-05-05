//
// BinaryProtocol.hh for BinaryProtocol in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 15:34:03 2015 Moghrabi Alexandre
// Last update Tue May  5 13:37:18 2015 Moghrabi Alexandre
//

/*!
 * \file BinaryProtocol
 * \brief Binary Protocol of the library
 * \author AlexMog
 * \version 1.2
 */

#ifndef MOGNETWORK_BINARYPROTOCOL_HH
# define MOGNETWORK_BINARYPROTOCOL_HH

# include "AProtocolListener.hh"

namespace mognetwork
{
  namespace protocol
  {
    /*!
     * \class BinaryProtocol
     * \brief Defines and execute the Binary protocol
     */
    class BinaryProtocol : public AProtocolListener
    {
    public:
      BinaryProtocol(TcpSocket* socket);
      virtual ~BinaryProtocol();

    public:
      virtual Socket::Status onReadTrigger();
      virtual bool datasFullyReceived();
      virtual void onSendDatas(const char* data, uint32_t size, TcpSocket::Data& dataToSend);
      virtual Socket::Status onReadAllTrigger(TcpSocket::Data& data);
    };
  }
}

#endif /* !MOGNETWORK_BINARYPROTOCOL_HH */
