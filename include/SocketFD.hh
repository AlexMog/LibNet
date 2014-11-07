//
// SocketFD.hh for SocketFD in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:12:47 2014 mognetworkhrabi Alexandre
// Last update Thu Jun  5 19:35:34 2014 mognetworkhrabi Alexandre
//

#include "OS.hh"

#ifndef SOCKETFD_HH
# define SOCKETFD_HH

#if defined(OS_WINDOWS)
typedef UINT_PTR SocketFD;
#else
typedef int SocketFD;
#endif

#endif // !SOCKETFD_HH
