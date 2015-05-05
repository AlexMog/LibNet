//
// BinaryProtocol.hh for BinaryProtocol in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 15:34:03 2015 Moghrabi Alexandre
// Last update Tue May  5 12:55:24 2015 Moghrabi Alexandre
//

/*!
 * \file TextProtocol
 * \brief Text Protocol of the library
 * \author AlexMog
 * \version 0.2
 */

#ifndef MOGNETWORK_TEXTPROTOCOL_HH
# define MOGNETWORK_TEXTPROTOCOL_HH

# include <iostream>
# include "AProtocolListener.hh"

namespace mognetwork
{
  namespace protocol
  {
    /*!
     * \class TextProtocol
     * \brief Defines and execute the Binary protocol
     */
    class TextProtocol : public AProtocolListener
    {
    public:
      TextProtocol(TcpSocket* socket, char* separator);
      virtual ~TextProtocol();

    public:
      virtual Socket::Status onReadTrigger();
      virtual bool datasFullyReceived();
      virtual void onSendDatas(const char* data, std::size_t size, TcpSocket::Data& dataToSend);
      virtual Socket::Status onReadAllTrigger(TcpSocket::Data& data);
      virtual TcpSocket::ReadedDatas& getReadedDatas();
      virtual void flushReader();

    private:
      TcpSocket::ReadedDatas* m_fullDatas;
      char* m_separator;
    };
  }
}

#endif /* !MOGNETWORK_TEXTPROTOCOL_HH */
