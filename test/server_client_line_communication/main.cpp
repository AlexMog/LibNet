#include <mognetwork/Packet.hh>
#include <mognetwork/TcpASIOServer.hh>
#include <stdio.h>
#include <iostream>
#include <exception>
#include <signal.h>

mognetwork::TcpASIOServer server(4242, mognetwork::TcpASIOServer::LinePerLine);

void shandler(int)
{
  std::cout << "Stopping server..." << std::endl;
  server.stop();
}

class Listener : public mognetwork::ITcpASIOListenerHandler
{
public:
  Listener(mognetwork::TcpASIOWriter* writer) : m_writer(writer) {}
  void onConnect(mognetwork::TcpSocket& client)
  {
    std::cout << "New client connected." << std::endl;
  }

  void onReceivedData(mognetwork::TcpSocket& client)
  {
    mognetwork::TcpSocket::ReadedDatas* datas = client.getDatasReaded();

    std::cout << "Received: " << &datas->datas[0] << std::endl;
    client.asyncSend("LOL\n\0", 5);
    m_writer->triggerData();
    delete datas;
  }

  void onDisconnect(mognetwork::TcpSocket& client) {std::cout << "Client disconnected." << std::endl;}
  
private:
  mognetwork::TcpASIOWriter* m_writer;
};

int main(int ac, char **av)
{
  Listener l(server.getServerWriter());

  signal(SIGINT, shandler);
  std::cout << "Starting server..." << std::endl;
  try {
    server.addListener(&l);
    server.start();
    std::cout << "Server ended." << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  std::cout << "Finish." <<std::endl;
  return (0);
}
