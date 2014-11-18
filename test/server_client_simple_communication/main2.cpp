#include <mognetwork/Packet.hh>
#include <mognetwork/TcpSocket.hh>
#include <stdio.h>
#include <iostream>
#include <exception>
#include <unistd.h>

int main(int ac, char **av)
{
  mognetwork::Packet packet;
  mognetwork::TcpSocket socket;
  mognetwork::IpAddress ip("127.0.0.1");
  std::string str = "LOL ITS A TEST\0";

  std::cout << "Connecting to server..." << std::endl;
  try {
    socket.connect(ip, 4242);
    packet << str.c_str();
    socket.send(reinterpret_cast<const char*>(packet.getData()), packet.getDataSize());
    sleep(5);
    socket.disconnect();
    sleep(5);
    std::cout << "Finished." << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  std::cout << "Finish." <<std::endl;
  return (0);
}
