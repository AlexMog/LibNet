//
// TcpSocket.hh for TCPSOCKET in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:59:35 2014 mognetworkhrabi Alexandre
// Last update Tue Nov 18 18:33:48 2014 Moghrabi Alexandre
//

/*!
 * \file TcpSocket.hh
 * \brief Gestion des sockets en TCP
 * \author AlexMog
 * \version 0.1
 */

#ifndef MOGNETWORK_TCPSOCKET_HH
# define MOGNETWORK_TCPSOCKET_HH

# include <list>
# include <vector>
# include <string>
# include "IpAddress.hh"
# include "Socket.hh"


namespace mognetwork
{
  class Packet;
  /*!
   * \class TcpSocket
   * \brief Classe de création d'une socket TCP
   */
  class TcpSocket : public Socket
  {
  public:
    typedef std::vector<char> Data; /*!< Typedef pour définit le typpage d'une Data */
    typedef std::list<Data> DataList; /*!< Typedef pour définit une dataList */

  public:
    /*!
     * \brief Contient toutes les données relatives à la lecture d'une donnée en réseau
     */
    struct ReadedDatas
    {
      ReadedDatas(); /*!< Constructeur pour réinitialiser la structure */
      std::size_t readed; /*!< Nombre d'octets lus */
      std::size_t totalSize; /*!< Taille totale à lire */
      Data datas; /*!< Données lues */
    };

    /*!
     * \brief Constructeur d'une socket en TCP par défaut
     */
    TcpSocket();
    /*!
     * \brief Constructeur d'une socket TCP à partir d'une socket déjà ouverte
     * \param fd le FD de la socket déjà ouverte
     */
    TcpSocket(SocketFD fd);
    /*!
     * \brief Connecte la socket à une adresse
     * \param address l'adresse où la socket doit se connecter
     * \param port le port où la socket doit se connecter
     */
    Socket::Status connect(const IpAddress& address, unsigned short port);
    /*!
     * \brief Déconnecte la socket
     */
    void disconnect();
    /*!
     * \brief Envois des données de manière synchrone (blockante)
     * \return Socket::Status permettant de savoir l'état de l'envois
     */
    Socket::Status send(const char* data, std::size_t size);
    /*!
     * \brief Reçoit des données de manière synchrone (blockante)
     * \return Socket::Status permettant de savoir l'état de la réception
     */
    Socket::Status receive(char* data, std::size_t size, std::size_t& received, int _flags);
    /*!
     * \brief Reçoit des données de manière synchrone (blockante)
     * \return Socket::Status permettant de savoir l'état de la réception
     */
    Socket::Status receiveAll(Data& data);
    /*!
     * \brief Ajoute des données à la liste d'envois des données de la socket en Asynchrone
     * \param data Les données à envoyer
     * \param size la taille totale des données
     * \return Socket::Status permettant de savoir l'état de l'envois
     */
    Socket::Status asyncSend(const char* data, std::size_t size);
    /*!
     * \brief Envois les données en attente ajoutées par asyncSend
     * \return Socket::Status permettant de savoir l'état de l'envois
     */
    Socket::Status sendPendingDatas();
    /*!
     * \brief Permet de savoir si il reste des données à envoyer via sendPendingDatas
     * \return true si il en reste, false sinon
     */
    bool havingPendingDatas() const;
    /*!
     * \brief Définit des données pouvant être récupérées via la socket
     * \param userData les données en question
     */
    void setUserData(void* userData);
    /*!
     * \brief Récupère des données enregistrées sur la socket
     * \return pointeur contenant les données
     */
    void* getUserData() const;
    /*!
     * \brief Lis les données en attente en Asynchrone
     * \return Socket::Status permettant de savoir l'état de la lecture
     */
    Socket::Status readPendingDatas();
    /*!
     * \brief Récupère les données lues via readPendingDatas
     * \return Les données lues en temps que TcpSocket::ReadedDatas
     */
    TcpSocket::ReadedDatas* getDatasReaded() const;
    /*!
     * \brief Récupère les données lues via readPendingDatas en temps que Packet
     * \return Les données en format Packet
     */
    Packet* getPacketReaded();

  private:
    DataList m_pendingDatas; /*!< Données en attente */
    ReadedDatas m_pendingRDatas; /*!< Données en attente de lecture */
    ReadedDatas *m_allDataReaded; /*!< Données lues */
    void* m_userData; /*!< Données supplémentaires optionnelles */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_TCPSOCKET_HH
