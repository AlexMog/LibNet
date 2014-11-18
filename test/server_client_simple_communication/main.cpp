#include <mognetwork/Packet.hh>
#include <mognetwork/TcpASIOServer.hh>
#include <mognetwork/TcpASIOWriter.hh>
#include <stdio.h>
#include <iostream>
#include <exception>

class Listener : public mognetwork::ITcpASIOListenerHandler
{
public:
  Listener(mognetwork::TcpASIOWriter* writer) : m_writer(writer) {}
  void onConnect(mognetwork::TcpSocket& client) {std::cout << "New client connected." << std::endl;}
  void onReceivedData(mognetwork::TcpSocket& client)
  {
    char buffer[42];
    mognetwork::Packet* packet = client.getPacketReaded();
    *packet >> buffer;
    std::cout << "RECEIVED: '" << buffer << "'" << std::endl;
    packet->clear();
    std::string s(buffer);
    *packet << s.c_str();
    client.asyncSend(reinterpret_cast<const char*>(packet->getData()), packet->getDataSize());
    m_writer->triggerData();
    delete packet;
  }

  void onDisconnect(mognetwork::TcpSocket& client) {std::cout << "Client disconnected." << std::endl;}
  
private:
  mognetwork::TcpASIOWriter* m_writer;
};

int main(int ac, char **av)
{
  mognetwork::TcpASIOServer server(4242);
  Listener l(server.getServerWriter());

  std::cout << "Starting server..." << std::endl;
  try {
    server.addListener(&l);
    server.start();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  std::cout << "Finish." <<std::endl;
  return (0);
}
