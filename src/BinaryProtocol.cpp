//
// BinaryProtocol.cpp for BinaryProtocol in /home/alexmog/projets/LibNet/src/protocols
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 15:40:07 2015 Moghrabi Alexandre
// Last update Mon Apr 20 02:45:37 2015 Moghrabi Alexandre
//

#include <cstring>
#include "mognetwork/OS.hh"
#ifdef OS_WINDOWS
#include <algorithm>
#endif // OS_WINDOWS
#include "mognetwork/BinaryProtocol.hh"

namespace mognetwork
{
  namespace protocol
  {
    Socket::Status BinaryProtocol::onReadTrigger()
    {
      std::size_t readed;
      char buffer[1024];

      // Get the size of the packet
      if (m_pendingDatas.readed < sizeof(std::size_t))
	{
	  char* data = reinterpret_cast<char*>(&m_pendingDatas.totalSize) + m_pendingDatas.readed;
	  Socket::Status status = m_socket->receive(data, sizeof(std::size_t) - m_pendingDatas.readed, readed, 0);
	  m_pendingDatas.readed += readed;
	  if (status != Socket::Ok)
	    return status;
	}
      // Read the packet
      if (m_pendingDatas.readed >= sizeof(std::size_t))
	{
	  std::size_t toGet = std::min(static_cast<std::size_t>(m_pendingDatas.totalSize - m_pendingDatas.datas.size()), sizeof(buffer));
	  Socket::Status status = m_socket->receive(buffer, toGet, readed, 0);
	  if (status != Socket::Ok)
	    return status;
	  m_pendingDatas.readed += readed;
	  if (readed > 0)
	    {
	      m_pendingDatas.datas.resize(m_pendingDatas.datas.size() + readed);
	      char* begin = &m_pendingDatas.datas[0] + m_pendingDatas.datas.size() - readed;
	      std::memcpy(begin, buffer, readed);
	    }
	}
      return Socket::Waiting;
    }

    bool BinaryProtocol::datasFullyReceived()
    {
      return m_pendingDatas.readed >= sizeof(std::size_t) && m_pendingDatas.readed >= m_pendingDatas.totalSize;
    }

    void BinaryProtocol::onSendDatas(const char* data, std::size_t size, TcpSocket::Data& dataToSend)
    {
      dataToSend.resize(size + sizeof(std::size_t));
      std::memcpy(&dataToSend.front(), &size, sizeof(std::size_t));
      std::memcpy(&dataToSend.front() + sizeof(std::size_t), data, size);
    }

    Socket::Status BinaryProtocol::onReadAllTrigger(TcpSocket::Data& data)
    {
      std::size_t readed = 0;
      char buffer[1024];
      std::size_t numReaded = 0;

      TcpSocket::ReadedDatas _data = TcpSocket::ReadedDatas();
      data.clear();
      while (readed < sizeof(std::size_t))
	{
	  char* d = reinterpret_cast<char*>(&_data.totalSize) + numReaded;
	  Socket::Status status = m_socket->receive(d, sizeof(std::size_t) - _data.readed, readed, 0);
	  numReaded += readed;
	  if (status != Socket::Ok)
	    return status;
	}
      if (numReaded >= sizeof(std::size_t))
	{
	  while (_data.readed < _data.totalSize)
	    {
	      std::size_t toGet = std::min(static_cast<std::size_t>(_data.totalSize - _data.readed),
					   sizeof(buffer));
	      Socket::Status status = m_socket->receive(buffer, toGet, readed, 0);
	      if (status != Socket::Ok)
		return status;
	      _data.readed += readed;
	      if (readed > 0)
		{
		  data.resize(data.size() + readed);
		  char* begin = &data[0] + data.size() - readed;
		  std::memcpy(begin, buffer, readed);
		}
	      if (_data.readed >= _data.totalSize)
		return Socket::Ok;
	    }
	}
      return Socket::Error;
    }
  }
}
