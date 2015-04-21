cmake_minimum_required(VERSION 2.8)

project(MogNetwork)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-g3 -W -Wall -pedantic -ansi")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(mognetwork SHARED
  src/UnixCondVar.cpp
  src/WinCondVar.cpp
  src/IpAddress.cpp
  src/WinMutex.cpp
  src/UnixMutex.cpp
  src/Packet.cpp
  src/Selector.cpp
  src/Socket.cpp
  src/TcpASIOServer.cpp
  src/TcpASIOListener.cpp
  src/TcpASIOWriter.cpp
  src/TcpServerSocket.cpp
  src/TcpSocket.cpp
  src/UnixThread.cpp
  src/WinThread.cpp
  src/UnixSocket.cpp
  src/WinSocket.cpp
  src/BinaryProtocol.cpp
  src/LineProtocol.cpp
  )

if(WIN32)
  target_link_libraries(mognetwork wsock32 ws2_32)
endif()  

install(TARGETS mognetwork DESTINATION lib)
install(DIRECTORY include DESTINATION .)
