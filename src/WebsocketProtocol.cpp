//
// BinaryProtocol.cpp for BinaryProtocol in /home/alexmog/projets/LibNet/src/protocols
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 15:40:07 2015 Moghrabi Alexandre
// Last update Tue Jul  7 16:32:53 2015 Moghrabi Alexandre
//

#include <iostream>
#include <cstring>
#include "mognetwork/OS.hh"
#ifdef OS_WINDOWS
# include <winsock2.h>
# include <algorithm>
#else
#include <arpa/inet.h>
#endif // OS_WINDOWS
#include "mognetwork/WebsocketProtocol.hh"
#include "mognetwork/ProtocolException.hpp"

namespace mognetwork
{
  namespace protocol
  {
    WebsocketProtocol::WebsocketProtocol(TcpSocket* socket) :
      AProtocolListener(socket) {}

    WebsocketProtocol::~WebsocketProtocol() {}

    Socket::Status WebsocketProtocol::onReadTrigger()
    {
      
      return Socket::Error;
    }

    int WebsocketProtocol::setHeader(Frame& frame)
    {
      int i, new_size;
      Frame::State state;

      state = frame.state;
      switch (state)
	{
	case STARTED:
	  if (frame.rawdata_idx < 2)
	    return 0;
	  frame.state = GOT_TWO;
	case GOT_TWO:
	  frame.mask_offset = 2;
	  frame.fin = (*(&frame.rawdata[0]) & 0x80) == 0x80 ? 1 : 0;
	  frame.opcode = *(&frame.rawdata[0]) & 0xf;
	  frame.payload_len_short = *(&frame.rawdata[0] + 1) & 0x7f;
	  frame.state = GOT_SHORT_LEN;
	case GOT_SHORT_LEN:
	  if (frame.payload_len_short == 126)
	    {
	      if (frame.rawdata_idx < 4)
		return 0;
	      frame.mask_offset += 2;
	      frame.payload_offset = frame.mask_offset + MASK_LENGTH;
	      frame.payload_len = ntohs(*((unsigned short int*) (&frame.rawdata[0] + 2)));
	    }
	  else if (frame.payload_len_short == 127)
	    {
	      if (frame.raxdata_idx < 10)
		return 0;
	      frame.mask_offset += 8;
	      frame.payload_offset = frame.mask_offset + MASK_LENGTH;
	      frame.payload_len = ntohl(*((unsinged short int*) (&frame.rawdata[0] + 6)));
	    }
	  else
	    {
	      frame.payload_len = frame.payload_len_short;
	      frame.payload_offset = frame.mask_offset + MASK_LENGTH;
	    }
	  frame.state = GOT_FULL_LEN;
	case GOT_FULL_LEN:
	  if (frame.rawdata_idx < frame.payload_offset)
	    return 0;
	  for (i = 0; i < MASK_LENGTH; ++i)
	    frame.mask[i] = *(&frame.rawdata[0] + frame.mask_offset + i) & 0xff;
	  frame.state = GOT_MASK;
	  frame.size = frame.payload_offset + frame.payload_len;
	  if (frame.size > frame.rawdata_sz)
	    {
	      new_size = frame.size - 1;
	      new_size |= new_size >> 1;
	      new_size |= new_size >> 2;
	      new_size |= new_size >> 4;
	      new_size |= new_size >> 8;
	      new_size |= new_size >> 16;
	      new_size++;
	      frame.rawdata_sz = new_size;
	      frame.rawdata.resize(new_size);
	    }
	  return 1;
	case GOT_MASK:
	  return 1;
	}
      return 0;
    }

    bool WebsocketProtocol::datasFullyReceived()
    {
      return false;
    }

    char* WebsocketProtocol::constructFrame(const char* data, uint32_t& size)
    {
      uint32_t* payload_len;
      unsigned short int* payload_len_short;
      unsigned char finNopcode, pauload_len_small;
      uins32_t playload_offset = 2;
      uint32_t frame_size;
      char* frame;

      finNopcode = 0xff;
      if (size <= 125)
	{
	  frame_size = 2 + size;
	  payload_len_small = size & 0xff;
	}
      else if (size > 125 && size <= 0xffff)
	{
	  frame_size = 4 + size;
	  payload_len_small = 126;
	  payload_offset += 2;
	}
      else if (size > 0xffff && size <= 0xfffffff0)
	{
	  frame_size = 10 + size;
	  pauload_len_small = 127;
	  payload_offset += 8;
	}
      else
	throw ProtocolException("LibNet does not support frame payload size too big.",
				__LINE__, __FILE__, __FUNC__);
      frame = new char[frame_size];
      m_frame.set(frame);
      payload_len_small &= 0x7f;
      *frame = finNopcode;
      *(frame + 1) = payload_len_small;
      if (playload_len_small == 126)
	{
	  size &= 0xffff;
	  payload_len_short = static_cast<unsigned int*>((char*) frame + 2);
	  *payload_len_short = htons(size);
	}
      if (payload_len_small == 127)
	{
	  payload_len = static_cast<unsigned int*>((char*) frame + 2);
	  *payload_len++ = 0;
	  *payload_len = htonl(size);
	}
      std::memcpy(frame + payload_offset, data, size);
      return frame;
    }

    void WebsocketProtocol::onSendDatas(const char* data, uint32_t size, TcpSocket::Data& dataToSend)
    {
      char* frame = constructFrame(data, size);
      dataToSend.resize(size);
      std::memcpy(&dataToSend.front(), frame, size);
      delete frame;
      m_frame.set(NULL);
    }

    Socket::Status WebsocketProtocol::onReadAllTrigger(TcpSocket::Data& data)
    {
      return Socket::Error;
    }
  }
}
