//
// AProtocolListener.cpp for AProtocolListener in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Apr 28 10:55:53 2015 Moghrabi Alexandre
// Last update Tue Apr 28 11:24:09 2015 Moghrabi Alexandre
//

#include "mognetwork/AProtocolListener.hh"

namespace mognetwork
{
  namespace protocol
  {
    AProtocolListener::AProtocolListener(TcpSocket* socket)
      : m_socket(socket) {}

    AProtocolListener::~AProtocolListener() {}

    TcpSocket::ReadedDatas& AProtocolListener::getReadedDatas()
    {
      return m_pendingDatas;
    }

    void AProtocolListener::flushReader()
    {
      m_pendingDatas = TcpSocket::ReadedDatas();
    }
  }
}
