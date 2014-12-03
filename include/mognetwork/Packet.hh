//
// Packet.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 18 09:41:30 2014 Moghrabi Alexandre
// Last update Thu Dec  4 00:34:18 2014 Moghrabi Alexandre
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
# include <arpa/inet.h>
# include "TcpSocket.hh"

namespace mognetwork
{
  /*!
   * \class Packet
   * \brief simplifie la gestion des données reçues
   */
  class Packet
  {
  public:
    /*/
     * \brief Constructeur par défaut
     */
    Packet();
    /*!
     * \brief Constructeur secondaire
     * \param data Un vecteur de données
     */
    Packet(std::vector<char>* data);
    /*!
     * \brief Constructeur via TcpSocet::ReadedDatas
     * \param La structure de données à utiliser
     */
    Packet(TcpSocket::ReadedDatas* data);
    virtual ~Packet();

    /*!
     * \brief extrait un uint32_t des données
     * \param data l'uint32_t dans lequel les données sont extraites
     */
    Packet& operator>>(uint32_t& data);
    /*!
     * \brief ajoute un uint32_t au packet
     * \param data l'uint32_t à ajouter
     */
    Packet& operator<<(uint32_t data);
    /*!
     * \brief ajoute un char* au packet
     * \param data le char* à ajouter
     */
    Packet& operator<<(const char* data);
    /*!
     * \brief extrait un char* du packet
     * \param data le char* dans lequel il sera extrait. Doit être alloué à la bonne taille.
     */
    Packet& operator>>(char* data);
    /*!
     * \brief extrait des données (natives de préférence) du packet
     * \param data la donnée sera ecrite dedans.
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
     * \brief ajoute des données (natives de préférence) au packet
     * \param data la donnée à ajouter
     */
    template <typename T>
    Packet& operator<<(const T& data)
    {
      push(&data, sizeof(data));
      return (*this);
    }
    /*!
     * \brief Permet de vider le packet
     */
    void clear() {m_data->clear();m_readerPos = 0;}
    /*!
     * \brief Permet de récupérer les données stockées dans le packet sous forme de void*
     * \return les données sous forme de void*
     */
    const void* getData() const {return (!m_data->empty() ? &((*m_data)[0]) : NULL);}
    /*!
     * \brief Permet de récupérer la taille du packet
     * \return la taille du packet
     */
    unsigned int getDataSize() const {return m_data->size();}
    /*!
     * \brief ajoute des données au packet
     * \param data Donnée à ajouter
     * \param size taille de la donnée
     */
    void push(const void* data, unsigned int size);

  private:
    bool verifySize(unsigned int size) {return (m_readerPos + size <= m_data->size());}

  private:
    std::vector<char>* m_data; /*!< Données du packet */
    unsigned int m_readerPos; /*!< Position du lecteur */
    TcpSocket::ReadedDatas* m_dataPack; /*!< Structure de données si elle est utilisée */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_PACKET_HH
