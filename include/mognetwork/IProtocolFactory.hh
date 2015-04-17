//
// ProtocolFactory.hh for ProtocolFactory in /home/alexmog/projets/LibNet/include/mognetwork
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 17:17:00 2015 Moghrabi Alexandre
// Last update Fri Apr 17 17:28:22 2015 Moghrabi Alexandre
//

#ifndef MOGNETWORK_IPROTOCOLFACTORY_HH
# define MOGNETWORK_IPROTOCOLFACTORY_HH

# include "AProtocolListener.hh"

namespace mognetwork
{
  class IProtocolFactory
  {
  public:
    virtual ~IProtocolFactory() {}
    virtual protocol::AProtocolListener* getNewObject(TcpSocket* socket) = 0;
  };
}
#endif /* !MOGNETWORK_IPROTOCOLFACTORY_HH */
