#include <mognetwork/Packet.hh>
#include <mognetwork/TcpSocket.hh>
#include <mognetwork/BinaryProtocol.hh>
#include <stdio.h>
#include <iostream>
#include <exception>
#include <unistd.h>
#include <sys/time.h>

#define NUMBER_OF_PACKET_SEND 10

int main(int ac, char **av)
{
  mognetwork::Packet packet;
  mognetwork::TcpSocket socket;
  socket.setProtocolListener(new mognetwork::protocol::BinaryProtocol(&socket));
  mognetwork::IpAddress ip("labs-epimars.eu");
  std::string str = "LOL ITS A TEST\0";
  int i = NUMBER_OF_PACKET_SEND;
  bool b = true;
  char c = 'c';
  double d = 10;
  float f = 1.2;
  int16_t i16 = 16;
  int32_t i32 = 32;
  int64_t i64 = 64;
  std::string s = "coucou\0";
  struct timeval t1, t2;
  double totalTime = 0;
  double latency = 0;

  packet << c;
  packet << d;
  packet << f;
  //  packet << i16;
  packet << i32;
  //  packet << i64;
  packet << s.c_str();
  packet << b;

  std::cout << "Connecting to server..." << std::endl;
  try {
    packet << str.c_str();
    socket.connect(ip, 4242);
    while (i > 0)
      {
	std::vector<char>* datas = new std::vector<char>;
	char buffer[1024];

	memset(buffer, 0, sizeof(buffer));
	socket.send((char*)packet.getData(), packet.getDataSize());
	gettimeofday(&t1, NULL);
	if (socket.receiveAll(*datas) != mognetwork::Socket::Ok)
	  {
	    perror("WTF?");
	    return 1;
	  }
	gettimeofday(&t2, NULL);
	latency = ((double) (t2.tv_usec - t1.tv_usec) / 1000 +
		   (double) (t2.tv_sec - t1.tv_sec));
	std::cout << "Lattency: " << latency << "ms" << std::endl;
	totalTime += latency;
	//	mognetwork::Packet p(datas);
	std::cout << "RECEIVED: S: '" << datas->size() << "' D: '" << (&(*datas)[0]) << "'" << std::endl;
	i--;
	delete datas;
	sleep(1);
      }
    socket.disconnect();
    std::cout << "Latency avg: " << (totalTime / NUMBER_OF_PACKET_SEND) << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  std::cout << "Finish." <<std::endl;
  return (0);
}
