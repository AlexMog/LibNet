cmake_minimum_required(VERSION 2.8)

project(MogNetwork)

set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(mognetwork SHARED
  src/CondVar.cpp
  src/IpAddress.cpp
  src/Mutex.cpp
  src/Packet.cpp
  src/Selector.cpp
  src/Socket.cpp
  src/TcpASIODatas.cpp
  src/TcpASIOListener.cpp
  src/TcpASIOServer.cpp
  src/TcpASIOWriter.cpp
  src/TcpServerSocket.cpp
  src/TcpSocket.cpp
  src/UnixThread.cpp
  src/WinThread.cpp
  src/UnixSocket.cpp
  src/WinSocket.cpp
  )
install(TARGETS mognetwork DESTINATION lib)
install(DIRECTORY include DESTINATION .)
