//
// BinaryProtocol.hh for BinaryProtocol in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 15:34:03 2015 Moghrabi Alexandre
// Last update Tue Jul  7 14:40:57 2015 Moghrabi Alexandre
//

/*!
 * \file WebsocketProtocol
 * \brief Websocket Protocol of the library
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_WEBSOCKETPROTOCOL_HH
# define MOGNETWORK_WEBSOCKETPROTOCOL_HH

# include <iostream>
# include "AProtocolListener.hh"

# define FRAME_CHUNK_LENGTH 1024

namespace mognetwork
{
  namespace protocol
  {
    /*!
     * \class WebsocketProtocol
     * \brief Defines and execute the Binary protocol
     */
    class WebsocketProtocol : public AProtocolListener
    {
    public:
      WebsocketProtocol(TcpSocket* socket, char* separator);
      virtual ~WebsocketProtocol();

    public:
      virtual Socket::Status onReadTrigger();
      virtual bool datasFullyReceived();
      virtual void onSendDatas(const char* data, uint32_t size, TcpSocket::Data& dataToSend);
      virtual Socket::Status onReadAllTrigger(TcpSocket::Data& data);
      virtual TcpSocket::ReadedDatas& getReadedDatas();
      virtual void flushReader();

    private:
      char* construct_frame(const char* data, uint32_t size);
      struct frame {
	uint32_t fin;
	uint32_t opcode;
	uint32_t mast_offset;
	uint32_t pauload_offset;
	uint32_t rawdata_idx;
	uint32_t rawdata_sz;
	uint32_t size;
	uint32_t payload_len_short;
	uint32_t payload_len;
	char* rawdata;
	unsigned char mask[4];
      };
    };
  }
}

#endif /* !MOGNETWORK_WEBSOCKETPROTOCOL_HH */
