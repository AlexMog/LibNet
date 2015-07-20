//
// BinaryProtocol.hh for BinaryProtocol in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 15:34:03 2015 Moghrabi Alexandre
// Last update Tue Jul  7 20:35:16 2015 Moghrabi Alexandre
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
# include "SmartPtr.hpp"
# include <vector>

# define FRAME_CHUNK_LENGTH 1024
# define MASK_LENGTH 4

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
      struct Frame {
	Frame();
	enum State {
	  STARTED = 0,
	  GOT_TWO,
	  GOT_SHORT_LEN,
	  GOT_FULL_LEN,
	  GOT_MASK
	};
	uint32_t fin;
	uint32_t opcode;
	uint32_t mask_offset;
	uint32_t payload_offset;
	uint32_t rawdata_idx;
	uint32_t rawdata_sz;
	uint32_t size;
	uint32_t payload_len_short;
	uint32_t payload_len;
	std::vector<char> rawdata;
	unsigned char mask[MASK_LENGTH];
	State state;
      };

    public:
      WebsocketProtocol(TcpSocket* socket);
      virtual ~WebsocketProtocol();

    public:
      virtual Socket::Status onReadTrigger();
      virtual bool datasFullyReceived();
      virtual void onSendDatas(const char* data, uint32_t size, TcpSocket::Data& dataToSend);
      virtual Socket::Status onReadAllTrigger(TcpSocket::Data& data);
      virtual void flushReader();

    private:
      char* constructFrame(const char* data, uint32_t& size);
      int setHeader(Frame& frame);
      
    private:
      SmartPtr<char> m_frame;
      Frame m_pendingFrame;
    };
  }
}

#endif /* !MOGNETWORK_WEBSOCKETPROTOCOL_HH */
