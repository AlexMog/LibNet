//
// TcpASIODatas.hh for LibNEt in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 18:28:09 2014 Moghrabi Alexandre
// Last update Tue Nov 18 09:28:53 2014 Moghrabi Alexandre
//

/*!
 * \file TcpASIODatas.hh
 * \brief Permet la gestion des données partagées des différents threads ASIO. Est un Singleton
 * \author AlexMog
 * \version 0.1
 */

#ifndef TCPASIODATAS_HH_
# define TCPASIODATAS_HH_

# include <list>
# include "TcpSocket.hh"
# include "Singleton.hh"

namespace mognetwork
{
  /*!
   * \class TcpASIODatas
   * \brief Permet la gestion des données partagées des différents threads ASIO. Est un Singleton
   */
  class TcpASIODatas
  {
  public:
    /*!
     * \brief Permet de récupérer l'instance du Singleton de TcpASIODatas
     * \return l'instance en question
     */
    static TcpASIODatas* getInstance() {return (&Singleton<TcpASIODatas>::Instance());}
    virtual ~TcpASIODatas();

  public:
    /*!
     * \brief Constructeur par défaut de TcpASIOData. A ne pas utiliser.
     * \depreciated A ne pas utiliser. Utilisée par le Singleton.
     */
    TcpASIODatas();

  public:
    /*!
     * \brief permet de récupérer un TcpSocket via son SocketFD.
     * \param fd le SocketFD à rechercher
     * \return le TcpSocket stocké
     */
    TcpSocket* getSocketByFd(SocketFD fd);
    /*!
     * \brief Permet de récupérer la liste des TcpSocket stochée
     * \return la liste des TcpSocket
     */
    std::list<TcpSocket*>* getSocketList() const {return m_socketList;}

  public:
    /*!
     * \brief Ajoute une socket à la liste des sockets
     * \param socket la TcpSocket à ajouter
     */
    void addSocket(TcpSocket* socket) {m_socketList->push_back(socket);}
    /*!
     * \brief Supprime une socket déjà ajoutée via son adresse
     * \param socket l'adresse de la TcpSocket à supprimer
     */
    void remSocket(TcpSocket* socket) {m_socketList->remove(socket);}
    /*!
     * \brief Supprime une socket déjà ajoutée via son SocketFD
     * \param socket la SocketFD de la socket à supprimer
     */
    void remSocket(SocketFD socket);

  private:
    std::list<TcpSocket*>* m_socketList; /*!< Liste des sockets partagées entre les threads ASIO */
  };
} // namespace mognetwork

#endif // !TCPASIODATAS_HH_
