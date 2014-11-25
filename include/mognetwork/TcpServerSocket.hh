//
// TcpServerSocket.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Mon Nov 17 17:41:35 2014 Moghrabi Alexandre
// Last update Tue Nov 18 13:12:12 2014 Moghrabi Alexandre
//

/*!
 * \file TcpServerSocket.hh
 * \brief Socket pour la gestion simplifiée du serveur
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_TCPSERVERSOCKET_HH
# define MOGNETWORK_TCPSERVERSOCKET_HH

# include "IpAddress.hh"
# include "TcpSocket.hh"

namespace mognetwork
{
  /*!
   * \class TcpServerSocket
   * \brief Socket pour la gestion simplifiée du serveur
   */
  class TcpServerSocket : public TcpSocket
  {
  public:
    /*!
     * \brief constructeur par défaut
     */
    TcpServerSocket();
    virtual ~TcpServerSocket();

  public:
    /*!
     * \brief Accepte une connexion client
     * \return un pointeur sur le nouveau client en TCP
     */
    TcpSocket* accept();
    /*!
     * \brief Bind la socket sur un port
     * \param port le port à binder
     */
    void bind(int port);
    // TODO:    void bind(const IpAddress& ipAddress, int port);
    /*!
     * \brief écoute sur la socket
     * \param maxWaitingList liste d'attente d'écoute maximale
     */
    void listen(int maxWaitingList);

  public:
    /*!
     * \brief permet de savoir si la socket a bien bind sur le port.
     * \return true si elle est bind, false sinon
     */
    bool isBound() const {return m_bound;}
    /*!
     * \brief permet de savoir si la socket écoute sur le port.
     * \ return true si oui, false sinon.
     */
    bool isListening() const {return m_listening;}

  private:
    bool m_bound; /*!< Stocke l'état du bind. */
    bool m_listening; /*!< Stocke l'état du listen. */
    int m_port; /*!< Stocke le port d'écoute */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_TCPSERVERSOCKET_HH
