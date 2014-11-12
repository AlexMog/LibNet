//
// TcpASIODatas.hh for LibNEt in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 18:28:09 2014 Moghrabi Alexandre
// Last update Wed Nov 12 19:17:31 2014 Moghrabi Alexandre
//

#ifndef TCPASIODATAS_HH_
# define TCPASIODATAS_HH_

# include <list>
# include "TcpSocket.hh"
# include "Singleton.hh"

namespace mognetwork
{
  class TcpASIODatas
  {
  public:
    static TcpASIODatas* getInstance() {return (&Singleton<TcpASIODatas>::Instance());}
    virtual ~TcpASIODatas();

  public:
    TcpASIODatas();

  public:
    TcpSocket* getSocketByFd(SocketFD fd);
    std::list<TcpSocket*>* getSocketList() const {return m_socketList;}

  public:
    void addSocket(TcpSocket* socket) {m_socketList->push_back(socket);}
    void remSocket(TcpSocket* socket) {m_socketList->remove(socket);}
    void remSocket(SocketFD socket);

  private:
    std::list<TcpSocket*>* m_socketList;
  };
}; // namespace mognetwork

#endif // !TCPASIODATAS_HH_
