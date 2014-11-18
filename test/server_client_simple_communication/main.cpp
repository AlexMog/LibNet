#include "TcpASIOServer.hh"
#include <stdio.h>
#include <iostream>
#include <exception>

class Listener : public ITcpASIOListenerHandler
{
public:
  void onConnect(TcpSocket& client) {std::cout << "New client connected." << std::endl;}
  void onReceivedData(TcpSocket& client) {std::cout << "Datas received: " << //TODO << std::endl;}
  void onDisconnect(TcpSocket& client) {std::cout << "Client disconnected." << std::endl;}
};

int main(int ac, char **av)
{
  mognetwork::TcpASIOServer server(42420);

  std::cout << "Starting server..." << std::endl;
  try {
    server.start();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    perror("WUUT?");
  }
  std::cout << "Finish." <<std::endl;
  return (0);
}
