//
// Packet.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 18 09:41:30 2014 Moghrabi Alexandre
// Last update Mon Dec 15 09:39:17 2014 Moghrabi Alexandre
//

/*!
 * \file Packet.hh
 * \brief Simplifie la gestion des données reçues
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_PACKET_HH
# define MOGNETWORK_PACKET_HH

# include <vector>
# include <string.h>
# include "OS.hh"
#ifndef OS_WINDOWS
# include <arpa/inet.h>
#endif // !OS_WINDOWS
# include "TcpSocket.hh"

namespace mognetwork
{
  /*!
   * \class Packet
   * \brief Simplify the data management of multiple datas
   */
  class Packet
  {
  public:
    /*/
     * \brief Default constructor
     */
    Packet();
    /*!
     * \brief Secondary constructor, uses a valid data set
     * \param data The data set
     */
    Packet(std::vector<char>* data);
    /*!
     * \brief Uses a TcpSocket::ReadedDatas to set the datas
     * \param data The datas
     */
    Packet(TcpSocket::ReadedDatas* data);
    virtual ~Packet();

    /*!
     * \brief Extract a uint32_t from the packet
     * \param data a reference on the uint32_t to set
     */
    Packet& operator>>(uint32_t& data);
    /*!
     * \brief add a uint32_t to the packet
     * \param data the uint32_t to add
     */
    Packet& operator<<(uint32_t data);
    /*!
     * \brief add a string to the packet
     * \param data the string to add
     */
    Packet& operator<<(const char* data);
    /*!
     * \brief extract a string from the packet
     * \param data the char* to set (it have to be a buffer with a size to receive the datas)
     */
    Packet& operator>>(char* data);
    /*!
     * \brief extract native datas from the packet
     * \param data the data to set
     */
    template <typename T>
    Packet& operator>>(T& data)
    {
      if (verifySize(sizeof(data)))
	{
	  data = *reinterpret_cast<const T*>(&((*m_data)[m_readerPos]));
	  m_readerPos += sizeof(data);
	}
      return (*this);
    }
    /*!
     * \brief add native datas to the packet
     * \param data the data to add
     */
    template <typename T>
    Packet& operator<<(const T& data)
    {
      push(&data, sizeof(data));
      return (*this);
    }
    /*!
     * \brief Clear the datas
     */
    void clear() {m_data->clear();m_readerPos = 0;}
    /*!
     * \brief Get the datas stored in the packet
     * \return the datas stored
     */
    const void* getData() const {return (!m_data->empty() ? &((*m_data)[0]) : NULL);}
    /*!
     * \brief Get the size of the datas stored
     * \return the datas size
     */
    unsigned int getDataSize() const {return m_data->size();}
    /*!
     * \brief add datas to the packet
     * \depreciated prefer to use the operator system
     * \param data Data to add
     * \param size Size of the data to add
     */
    void push(const void* data, unsigned int size);

  private:
    bool verifySize(unsigned int size) {return (m_readerPos + size <= m_data->size());}

  private:
    std::vector<char>* m_data; /*!< Datas of the packet */
    unsigned int m_readerPos; /*!< Actual position reader */
    TcpSocket::ReadedDatas* m_dataPack; /*!< datas structure if set */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_PACKET_HH
