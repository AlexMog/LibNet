//
// SocketSelectorListener.hh for SocketSelectorListener in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Oct 10 15:31:21 2014 mognetworkhrabi Alexandre
// Last update Wed Nov 12 14:25:49 2014 Moghrabi Alexandre
//

#ifndef SOCKETSELECTORLISTENER_HH_
# define SOCKETSELECTORLISTENER_HH_

/*!
 * \file SocketSelectorListener.hh
 * \brief Doit être supprimé plus tard.
 * \depreciated Va être supprimé
 */

# include "TcpSocket.hh"

namespace mognetwork
{
class SocketSelectorListener
{
public:
  virtual ~SocketSelectorListener();

public:
  virtual void clientAccepted(TcpSocket& client);
  virtual void clientDatasReceived(TcpSocket& client);
  virtual void clientDisconnected(TcpSocket& client);
};
}

#endif /* !SOCKETSELECTORLISTENER_HH_ */
