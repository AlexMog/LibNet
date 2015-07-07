//
// BinaryProtocolFactory.hh for BinaryProtocolFactory in /home/alexmog/projets/LibNet
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 17:20:30 2015 Moghrabi Alexandre
// Last update Tue Jul  7 14:58:43 2015 Moghrabi Alexandre
//

#ifndef MOGNETWORK_WEBSOCKETPROTOCOLFACTORY_HPP
# define MOGNETWORK_WEBSOCKETPROTOCOLFACTORY_HPP

# include "WebsocketProtocol.hh"
# include "IProtocolFactory.hh"

namespace mognetwork
{
  class WebsocketProtocolFactory : public IProtocolFactory
  {
  public:
    virtual protocol::AProtocolListener* getNewObject(TcpSocket* socket)
    {
      return (new protocol::WebsocketProtocol(socket));
    }
  };
}
#endif /* !MOGNETWORK_WEBSOCKETPROTOCOLFACTORY_HPP */
