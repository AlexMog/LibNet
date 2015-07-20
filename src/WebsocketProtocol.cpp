//
// BinaryProtocol.cpp for BinaryProtocol in /home/alexmog/projets/LibNet/src/protocols
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 15:40:07 2015 Moghrabi Alexandre
// Last update Mon Jul 13 12:35:17 2015 Moghrabi Alexandre
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
#include "mognetwork/ITcpASIOListenerHandler.hh"
#include "mognetwork/TcpASIOServer.hh"
#include "mognetwork/SmartPtr.hpp"

namespace mognetwork
{
  namespace protocol
  {
    WebsocketProtocol::WebsocketProtocol(TcpSocket* socket) :
      AProtocolListener(socket) {}

    WebsocketProtocol::~WebsocketProtocol() {}

    WebsocketProtocol::Frame::Frame()
      : fin(0),
	opcode(0),
	mask_offset(0),
	payload_offset(0),
	rawdata_idx(0),
	rawdata_sz(FRAME_CHUNK_LENGTH),
	size(0),
	payload_len_short(0),
	payload_len(-1),
	rawdata(FRAME_CHUNK_LENGTH),
	state(STARTED)
    {}
    
    Socket::Status WebsocketProtocol::onReadTrigger()
    {
      std::size_t i;
      int err;
      std::size_t readed;
      char buf[1024];
      char* buffer = (char*)buf;

      Socket::Status status = m_socket->receive(buf, 1024, readed, 0);
      if (status != Socket::Ok)
	return status;
      for (i = 0; i < readed;)
	{
	  *(&m_pendingFrame.rawdata[0] + m_pendingFrame.rawdata_idx++) = *buffer++;
	  ++i;
	  if (m_pendingFrame.state != Frame::GOT_MASK)
	    {
	      err = setHeader(m_pendingFrame);
	      if (err == 0)
		continue;
	    }
	  
	  if (m_pendingFrame.rawdata_idx < m_pendingFrame.size)
	    {
	      if (readed - i >= m_pendingFrame.size - m_pendingFrame.rawdata_idx) // Complete frame
		{
		  std::memcpy(&m_pendingFrame.rawdata[0] + m_pendingFrame.rawdata_idx, buffer,
			      m_pendingFrame.size - m_pendingFrame.rawdata_idx);
		  buffer += m_pendingFrame.size - m_pendingFrame.rawdata_idx;
		  i += m_pendingFrame.size - m_pendingFrame.rawdata_idx;
		  m_pendingFrame.rawdata_idx = m_pendingFrame.size;
		  TcpSocket::ReadedDatas* dat = new TcpSocket::ReadedDatas;
		  dat->datas.resize(m_pendingFrame.rawdata.size());
		  std::memcpy(&dat->datas[0],
			      &m_pendingFrame.rawdata[0],
			      m_pendingFrame.rawdata.size());
		  m_pendingFrame = Frame();
		  m_socket->setAllDataReaded(dat);
		  for (std::list<ITcpASIOListenerHandler*>::iterator it = m_socket->getServer()->getServerListener()->getListeners().begin();
		       it != m_socket->getServer()->getServerListener()->getListeners().end(); ++it)
		    (*it)->onReceivedData(*m_socket);
		  dat = NULL;
		}
	      else // Not complete frame
		{
		  std::memcpy(&m_pendingFrame.rawdata[0] + m_pendingFrame.rawdata_idx, buffer, readed - i);
		  m_pendingFrame.rawdata_idx += readed - i;
		  i = readed;
		}
	    }
	}
      return Socket::Error;
    }

    void WebsocketProtocol::flushReader()
    {
      m_pendingFrame = Frame();
    }

    int WebsocketProtocol::setHeader(Frame& frame)
    {
      int i, new_size;
      Frame::State state;

      state = frame.state;
      switch (state)
	{
	case Frame::STARTED:
	  if (frame.rawdata_idx < 2)
	    return 0;
	  frame.state = Frame::GOT_TWO;
	case Frame::GOT_TWO:
	  frame.mask_offset = 2;
	  frame.fin = (*(&frame.rawdata[0]) & 0x80) == 0x80 ? 1 : 0;
	  frame.opcode = *(&frame.rawdata[0]) & 0xf;
	  frame.payload_len_short = *(&frame.rawdata[0] + 1) & 0x7f;
	  frame.state = Frame::GOT_SHORT_LEN;
	case Frame::GOT_SHORT_LEN:
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
	      if (frame.rawdata_idx < 10)
		return 0;
	      frame.mask_offset += 8;
	      frame.payload_offset = frame.mask_offset + MASK_LENGTH;
	      frame.payload_len = ntohl(*((unsigned short int*) (&frame.rawdata[0] + 6)));
	    }
	  else
	    {
	      frame.payload_len = frame.payload_len_short;
	      frame.payload_offset = frame.mask_offset + MASK_LENGTH;
	    }
	  frame.state = Frame::GOT_FULL_LEN;
	case Frame::GOT_FULL_LEN:
	  if (frame.rawdata_idx < frame.payload_offset)
	    return 0;
	  for (i = 0; i < MASK_LENGTH; ++i)
	    frame.mask[i] = *(&frame.rawdata[0] + frame.mask_offset + i) & 0xff;
	  frame.state = Frame::GOT_MASK;
	  frame.size = frame.payload_offset + frame.payload_len;
	  if (frame.size > frame.rawdata_sz)
	    {
	      new_size = frame.size - 1;
	      new_size |= new_size >> 1;
	      new_size |= new_size >> 2;
	      new_size |= new_size >> 4;
	      new_size |= new_size >> 8;
	      new_size |= new_size >> 16;
	      ++new_size;
	      frame.rawdata_sz = new_size;
	      frame.rawdata.resize(new_size);
	    }
	  return 1;
	case Frame::GOT_MASK:
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
      unsigned char finNopcode, payload_len_small;
      uint32_t payload_offset = 2;
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
	  payload_len_small = 127;
	  payload_offset += 8;
	}
      else
	throw ProtocolException("LibNet does not support frame payload size too big.",
				__LINE__, __FILE__, __func__);
      frame = new char[frame_size];
      m_frame.set(frame);
      payload_len_small &= 0x7f;
      *frame = finNopcode;
      *(frame + 1) = payload_len_small;
      if (payload_len_small == 126)
	{
	  size &= 0xffff;
	  payload_len_short = reinterpret_cast<unsigned short*>((char*) frame + 2);
	  *payload_len_short = htons(size);
	}
      if (payload_len_small == 127)
	{
	  payload_len = reinterpret_cast<unsigned int*>((char*) frame + 2);
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
      // TODO error deletE?
      delete[] frame;
      m_frame.set(NULL);
    }

    Socket::Status WebsocketProtocol::onReadAllTrigger(TcpSocket::Data& data)
    {
      (void)data;
      return Socket::Error;
    }
  }
}
