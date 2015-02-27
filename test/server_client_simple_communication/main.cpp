#include <mognetwork/Packet.hh>
#include <mognetwork/TcpASIOServer.hh>
#include <mognetwork/TcpASIOWriter.hh>
#include <stdio.h>
#include <iostream>
#include <exception>
#include <signal.h>

mognetwork::TcpASIOServer server(4242);

void shandler(int)
{
  std::cout << "Stopping server..." << std::endl;
  server.stop();
}

class Listener : public mognetwork::ITcpASIOListenerHandler
{
public:
  Listener(mognetwork::TcpASIOWriter* writer) : m_writer(writer) {}
  void onConnect(mognetwork::TcpSocket& client) {std::cout << "New client connected." << std::endl;client.asyncSend("LOL\0", 4);
    m_writer->triggerData();}
  void onReceivedData(mognetwork::TcpSocket& client)
  {
    char buffer[42] = {0};
    char c = 0;
    //    int16_t i16 = 0;
    int32_t i32 = 0;
    //    int64_t i64 = 0;
    double d = 0;
    float f = 0;
    bool b = false;

    mognetwork::Packet* packet = client.getPacketReaded();
    //    mognetwork::TcpSocket::ReadedDatas* datas = client.getDatasReaded();
    (*packet) >> c;
    (*packet) >> d;
    (*packet) >> f;
    //    (*packet) >> i16;
    (*packet) >> i32;
    //    (*packet) >> i64;
    (*packet) >> buffer;
    (*packet) >> b;

    std::cout << "char: " << c << " (intval:" << (int)c << " )" << std::endl;
    std::cout << "double: " << d << std::endl;
    std::cout << "float: " << f << std::endl;
    //    std::cout << "int16: " << i16 << std::endl;
    std::cout << "int32: " << i32 << std::endl;
    //    std::cout << "int64: " << i64 << std::endl;
    std::cout << "String: '" << buffer << "'" << std::endl;
    std::cout << "bool: " << b << std::endl;
    
    client.asyncSend("LOL\0", 4);
    m_writer->triggerData();
    delete packet;
    //delete datas;
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
