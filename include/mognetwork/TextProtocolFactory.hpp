//
// BinaryProtocolFactory.hh for BinaryProtocolFactory in /home/alexmog/projets/LibNet
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Fri Apr 17 17:20:30 2015 Moghrabi Alexandre
// Last update Tue May  5 12:29:50 2015 Moghrabi Alexandre
//

#ifndef MOGNETWORK_TEXTPROTOCOLFACTORY_HPP
# define MOGNETWORK_TEXTPROTOCOLFACTORY_HPP

# include "TextProtocol.hh"
# include "IProtocolFactory.hh"

namespace mognetwork
{
  class TextProtocolFactory : public IProtocolFactory
  {
  public:
    TextProtocolFactory(char* separator) : m_separator(separator) {}

  public:
    virtual protocol::AProtocolListener* getNewObject(TcpSocket* socket)
    {
      return (new protocol::TextProtocol(socket, m_separator));
    }

  private:
    char* m_separator;
  };
}
#endif /* !MOGNETWORK_TEXTPROTOCOLFACTORY_HPP */
