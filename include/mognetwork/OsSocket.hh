//
// OsSocket.hh for OsSocket in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 19:34:20 2014 mognetworkhrabi Alexandre
// Last update Wed Oct  8 08:05:50 2014 mognetworkhrabi Alexandre
//

#include "OS.hh"
#if defined(OS_WINDOWS)
#include "WinSocket.hh"
#else
#include "UnixSocket.hh"
#endif
