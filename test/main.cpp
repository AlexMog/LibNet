#include "TcpASIOServer.hh"
#include <stdio.h>
#include <iostream>
#include <exception>

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
