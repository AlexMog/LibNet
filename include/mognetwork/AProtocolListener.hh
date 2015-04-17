//
// AProtocolListener.hh for ProtocolListener in /home/alexmog/projets/LibNet/include/mognetwork
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 15:05:31 2015 Moghrabi Alexandre
// Last update Fri Apr 17 17:07:43 2015 Moghrabi Alexandre
//

#ifndef MOGNETWORK_APROTOCOLLISTENER_HH
# define MOGNETWORK_APROTOCOLLISTENER_HH

# include "TcpSocket.hh"

namespace mognetwork
{
  namespace protocol
  {
    class AProtocolListener
    {
    public:
      AProtocolListener(TcpSocket* socket) : m_socket(socket) {}
      virtual ~AProtocolListener() {}
      
    public:
      virtual Socket::Status onReadTrigger() = 0;
      virtual bool datasFullyReceived() = 0;
      virtual void onSendDatas(const char* data, std::size_t size, TcpSocket::Data& dataToSend) = 0;
      virtual Socket::Status onReadAllTrigger(TcpSocket::Data& data) = 0;
      virtual TcpSocket::ReadedDatas& getReadedDatas() {return m_pendingDatas;}
      virtual void flushReader() {m_pendingDatas = TcpSocket::ReadedDatas();}
      
    protected:
      TcpSocket* m_socket;
      TcpSocket::ReadedDatas m_pendingDatas;
    };
  }
}
#endif /* !MOGNETWORK_APROTOCOLLISTENER_HH */
