//
// BinaryProtocol.hh for BinaryProtocol in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 15:34:03 2015 Moghrabi Alexandre
// Last update Tue Apr 28 10:53:49 2015 Moghrabi Alexandre
//

/*!
 * \file LineProtocol
 * \brief Line Protocol of the library
 * \author AlexMog
 * \version 0.2
 */

#ifndef MOGNETWORK_LINEPROTOCOL_HH
# define MOGNETWORK_LINEPROTOCOL_HH

# include <iostream>
# include "AProtocolListener.hh"

namespace mognetwork
{
  namespace protocol
  {
    /*!
     * \class LineProtocol
     * \brief Defines and execute the Binary protocol
     */
    class LineProtocol : public AProtocolListener
    {
    public:
      LineProtocol(TcpSocket* socket);
      virtual ~LineProtocol();

    public:
      virtual Socket::Status onReadTrigger();
      virtual bool datasFullyReceived();
      virtual void onSendDatas(const char* data, std::size_t size, TcpSocket::Data& dataToSend);
      virtual Socket::Status onReadAllTrigger(TcpSocket::Data& data);
      virtual TcpSocket::ReadedDatas& getReadedDatas() {return *m_fullDatas;}
      virtual void flushReader()
      {
	m_pendingDatas = TcpSocket::ReadedDatas();
	m_fullDatas = NULL;
      }

    private:
      TcpSocket::ReadedDatas* m_fullDatas;
    };
  }
}

#endif /* !MOGNETWORK_LINEPROTOCOL_HH */
