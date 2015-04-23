//
// BinaryProtocolFactory.hh for BinaryProtocolFactory in /home/alexmog/projets/LibNet
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 17:20:30 2015 Moghrabi Alexandre
// Last update Mon Apr 20 04:20:49 2015 Moghrabi Alexandre
//

#ifndef MOGNETWORK_LINEPROTOCOLFACTORY_HPP
# define MOGNETWORK_LINEPROTOCOLFACTORY_HPP

# include "LineProtocol.hh"
# include "IProtocolFactory.hh"

namespace mognetwork
{
  class LineProtocolFactory : public IProtocolFactory
  {
  public:
    virtual protocol::AProtocolListener* getNewObject(TcpSocket* socket)
    {
      return (new protocol::LineProtocol(socket));
    }
  };
}
#endif /* !MOGNETWORK_LINEPROTOCOLFACTORY_HPP */
