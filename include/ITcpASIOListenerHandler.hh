//
// ITcpASIOListenerHandler.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 00:44:56 2014 Moghrabi Alexandre
// Last update Tue Nov 11 17:34:21 2014 Moghrabi Alexandre
//

#ifndef ITCPASIOLISTENERHANDLER_HH_
# define ITCPASIOLISTENERHANDLER_HH_

# include "TcpSocket.hh"

namespace mognetwork
{
  class ITcpASIOListenerHandler
  {
  public:
    virtual void onReceivedData(TcpSocket& client) = 0;
    virtual void onDisconnect(TcpSocket& client) = 0;
  };
}; // namespace mognetwork

#endif // !ITCPASIOLISTENERHANDLER_HH_
