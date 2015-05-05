#include <mognetwork/Packet.hh>
#include <mognetwork/TcpSocket.hh>
#include <mognetwork/TextProtocol.hh>
#include <stdio.h>
#include <iostream>
#include <exception>
#include <unistd.h>
#include <sys/time.h>

#define NUMBER_OF_PACKET_SEND 10

int main(int ac, char **av)
{
  mognetwork::TcpSocket socket;
  socket.setProtocolListener(new mognetwork::protocol::TextProtocol(&socket, (char*)"\n"));
  mognetwork::IpAddress ip("127.0.0.1");
  int i = NUMBER_OF_PACKET_SEND;
  struct timeval t1, t2;
  double totalTime = 0;
  double latency = 0;

  std::cout << "Connecting to server..." << std::endl;
  try {
    socket.connect(ip, 4242);
    while (i > 0)
      {
	std::vector<char>* datas = new std::vector<char>;
	char buffer[1024];

	memset(buffer, 0, sizeof(buffer));
	socket.send("c\nb", 4);
	gettimeofday(&t1, NULL);
	if (socket.receiveAll(*datas) != mognetwork::Socket::Ok)
	  {
	    std::cout << "ERROR" << std::endl;
	    perror("WTF?");
	    return 1;
	  }
	gettimeofday(&t2, NULL);
	latency = ((double) (t2.tv_usec - t1.tv_usec) / 1000 +
		   (double) (t2.tv_sec - t1.tv_sec));
	std::cout << "RECEIVED: S: '" << datas->size() << "' D: '" << (&(*datas)[0]) << "'" << std::endl;
	std::cout << "Lattency: " << latency << "ms" << std::endl;
	totalTime += latency;
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
