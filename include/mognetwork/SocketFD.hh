//
// SocketFD.hh for SocketFD in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:12:47 2014 mognetworkhrabi Alexandre
// Last update Tue Nov 18 13:09:27 2014 Moghrabi Alexandre
//

#include "OS.hh"

#ifndef MOGNETWORK_SOCKETFD_HH
# define MOGNETWORK_SOCKETFD_HH

#if defined(OS_WINDOWS)
# include <windows.h>
typedef UINT_PTR SocketFD;
#else
typedef int SocketFD;
#endif

#endif // !MOGNETWORK_SOCKETFD_HH
