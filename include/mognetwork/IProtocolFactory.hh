//
// ProtocolFactory.hh for ProtocolFactory in /home/alexmog/projets/LibNet/include/mognetwork
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 17:17:00 2015 Moghrabi Alexandre
// Last update Mon Apr 20 02:03:36 2015 Moghrabi Alexandre
//

/*!
 * \file IProtocolFactory.hh
 * \brief Protocol factory
 * \author AlexMog
 * \version 0.2
 */

#ifndef MOGNETWORK_IPROTOCOLFACTORY_HH
# define MOGNETWORK_IPROTOCOLFACTORY_HH

# include "AProtocolListener.hh"

namespace mognetwork
{
  /*!
   * \class IProtocolFactory
   * \brief This Interface is used to create a ProtocolFactory who is used by the TcpASIOListener to set the socket protocol
   */
  class IProtocolFactory
  {
  public:
    virtual ~IProtocolFactory() {}
    /*!
     * \brief Generate a new AProtocolListener Object
     * \return A new instance of the protocol
     */
    virtual protocol::AProtocolListener* getNewObject(TcpSocket* socket) = 0;
  };
}
#endif /* !MOGNETWORK_IPROTOCOLFACTORY_HH */
