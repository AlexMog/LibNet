//
// BinaryProtocol.hh for BinaryProtocol in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 15:34:03 2015 Moghrabi Alexandre
// Last update Fri Apr 17 16:48:03 2015 Moghrabi Alexandre
//

#ifndef MOGNETWORK_BINARYPROTOCOL_HH
# define MOGNETWORK_BINARYPROTOCOL_HH

# include "AProtocolListener.hh"

namespace mognetwork
{
  namespace protocol
  {
    class BinaryProtocol : public AProtocolListener
    {
    public:
      BinaryProtocol(TcpSocket* socket) : AProtocolListener(socket) {}
      virtual ~BinaryProtocol() {}

    public:
      virtual Socket::Status onReadTrigger();
      virtual bool datasFullyReceived();
      virtual void onSendDatas(const char* data, std::size_t size, TcpSocket::Data& dataToSend);
      virtual Socket::Status onReadAllTrigger(TcpSocket::Data& data);
      virtual TcpSocket::ReadedDatas& getReadedDatas();
    };
  }
}

#endif /* !MOGNETWORK_BINARYPROTOCOL_HH */
