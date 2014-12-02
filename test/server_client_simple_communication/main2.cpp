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
  int i = 10;

  std::cout << "Connecting to server..." << std::endl;
  try {
    packet << str.c_str();
    socket.connect(ip, 4242);
    while (i > 0)
      {
	std::vector<char>* datas = new std::vector<char>;
	char buffer[1024];

	memset(buffer, 0, sizeof(buffer));
	socket.send(str.c_str(), 15);
	if (socket.receiveAll(*datas) != mognetwork::Socket::Ok)
	  {
	    std::cout << "ERROR" << std::endl;
	    perror("WTF?");
	    return 1;
	  }
	//	mognetwork::Packet p(datas);
	std::cout << "RECEIVED: S: '" << datas->size() << "' D: '" << (&(*datas)[0]) << "'" << std::endl;
	i--;
	delete datas;
	sleep(1);
      }
    socket.disconnect();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  std::cout << "Finish." <<std::endl;
  return (0);
}
