//
// TcpSocket.hh for TCPSOCKET in 
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:59:35 2014 Moghrabi Alexandre
// Last update Fri Oct 10 15:55:58 2014 Moghrabi Alexandre
//

#ifndef TCPSOCKET_HH
# define TCPSOCKET_HH

# include <list>
# include <vector>
# include <string>
# include "IpAddress.hh"
# include "Socket.hh"

namespace Mog
{
  class TcpSocket : public Socket
  {
  public:
    typedef void (*ReadFunction)(TcpSocket* client);
    typedef std::vector<char> Data;
    typedef std::list<Data> DataList;

  public:
    struct ReadedDatas
    {
      ReadedDatas();
      std::size_t readed;
      std::size_t totalSize;
      Data datas;
    };
    TcpSocket();
    TcpSocket(SocketFD fd);
    Socket::Status connect(const IpAddress& address, unsigned short port);
    void disconnect();
    Socket::Status send(const char* data, std::size_t size);
    Socket::Status receive(char* data, std::size_t size, std::size_t& received, int _flags);
    Socket::Status asyncSend(const char* data, std::size_t size);
    Socket::Status sendPendingDatas();
    bool havingPendingDatas() const;
    void setUserData(void* userData);
    void* getUserData() const;
    Socket::Status readPendingDatas();
    void setReadFunc(ReadFunction);
    const TcpSocket::ReadedDatas& getDatasReaded() const;

  private:
    DataList m_pendingDatas;
    ReadedDatas m_pendingRDatas;
    ReadedDatas m_allDataReaded;
    void* m_userData;
    ReadFunction m_readFunction;
  };
} // namespace Mog

#endif // !TCPSOCKET_HH
