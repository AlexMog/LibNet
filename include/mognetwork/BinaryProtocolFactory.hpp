//
// BinaryProtocolFactory.hh for BinaryProtocolFactory in /home/alexmog/projets/LibNet
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 17:20:30 2015 Moghrabi Alexandre
// Last update Fri Apr 17 17:27:39 2015 Moghrabi Alexandre
//

#ifndef MOGNETWORK_BINARYPROTOCOLFACTORY_HPP
# define MOGNETWORK_BINARYPROTOCOLFACTORY_HPP

# include "BinaryProtocol.hh"
# include "IProtocolFactory.hh"

namespace mognetwork
{
  class BinaryProtocolFactory : public IProtocolFactory
  {
  public:
    virtual protocol::AProtocolListener* getNewObject(TcpSocket* socket)
    {
      return (new protocol::BinaryProtocol(socket));
    }
  };
}
#endif /* !MOGNETWORK_BINARYPROTOCOLFACTORY_HPP */
