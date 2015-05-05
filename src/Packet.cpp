//
// Packet.cpp for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 18 09:52:30 2014 Moghrabi Alexandre
// Last update Tue May  5 13:53:13 2015 Moghrabi Alexandre
//

#include <iostream>
#include "mognetwork/Packet.hh"

namespace mognetwork
{
  Packet::Packet() : m_readerPos(0), m_dataPack(NULL)
  {
    m_data = new std::vector<char>;
  }

  Packet::Packet(std::vector<char>* data) : m_readerPos(0), m_dataPack(NULL)
  {
    m_data = data;
  }

  Packet::Packet(TcpSocket::ReadedDatas* data) : m_readerPos(0)
  {
    m_dataPack = data;
    m_data = &m_dataPack->datas;
  }

  Packet::~Packet()
  {
    if (m_dataPack != NULL)
      delete m_dataPack;
    else if (m_data != NULL)
      delete m_data;
  }

  Packet& Packet::operator>>(uint32_t& data)
  {
    if (verifySize(sizeof(data)))
      {
	data = ntohl(*reinterpret_cast<const uint32_t*>(&((*m_data)[m_readerPos])));
	m_readerPos += sizeof(data);
      }
    return (*this);
  }

  Packet& Packet::operator>>(uint16_t& data)
  {
    if (verifySize(sizeof(data)))
      {
	data = ntohs(*reinterpret_cast<const uint16_t*>(&((*m_data)[m_readerPos])));
	m_readerPos += sizeof(data);
      }
    return *this;
  }

  Packet& Packet::operator<<(uint32_t data)
  {
    uint32_t write = htonl(data);
    push(&write, sizeof(write));
    return (*this);
  }

  Packet& Packet::operator<<(uint16_t data)
  {
    uint16_t write = htons(data);
    push(&write, sizeof(write));
    return *this;
  }

  Packet& Packet::operator>>(char* data)
  {
    int32_t size = 0;
    *this >> size;

    if (size > 0 && verifySize(size))
      {
	memcpy(data, &((*m_data)[m_readerPos]), size);
	data[size] = '\0';
	m_readerPos += size;
      }
    return (*this);
  }

  Packet& Packet::operator>>(std::string& data)
  {
    int32_t size = 0;
    *this >> size;

    if (size > 0 && verifySize(size))
      {
	char *buffer = new char[size + 1];
	memcpy(buffer, &((*m_data)[m_readerPos]), size);
	buffer[size] = '\0';
	m_readerPos += size;
	data.append(buffer);
	delete buffer;
      }
    return (*this);
  }

  Packet& Packet::operator<<(const std::string& data)
  {
    int32_t size = data.size();
    *this << size;
    push(data.c_str(), size);
    return (*this);
  }

  Packet& Packet::operator<<(const char* data)
  {
    int32_t size = strlen(data) * sizeof(char);
    *this << size;
    push(data, size);
    return (*this);
  }

  void Packet::push(const void* data, unsigned int size)
  {
    unsigned int actualSize;

    if (data && size > 0)
      {
	actualSize = m_data->size();
	m_data->resize(actualSize + size);
	memcpy(&((*m_data)[actualSize]), data, size);
      }
  }

  void Packet::clear()
  {
    if (m_data != NULL)
      m_data->clear();
    m_readerPos = 0;
  }

  void Packet::reinitialize(TcpSocket::ReadedDatas* data)
  {
    m_readerPos = 0;
    if (m_dataPack != NULL)
      delete m_dataPack;
    else if (m_data != NULL)
      delete m_data;
    m_dataPack = data;
    m_data = &m_dataPack->datas;
  }

  void Packet::reinitialize(std::vector<char>* data)
  {
    m_readerPos = 0;
    if (m_dataPack != NULL)
      delete m_dataPack;
    else if (m_data != NULL)
      delete m_data;
    m_dataPack = NULL;
    m_data = data;    
  }
} // namespace mognetwork
