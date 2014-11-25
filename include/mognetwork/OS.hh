//
// OS.hh for OS in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 18:44:24 2014 mognetworkhrabi Alexandre
// Last update Tue Nov 18 13:10:21 2014 Moghrabi Alexandre
//

#ifndef MOGNETWORK_OS_HH
# define MOGNETWORK_OS_HH

// Find the operating system
#if defined(_WIN32) || defined(__WIN32__)

// Windows
#define OS_WINDOWS

#elif defined(linux) || defined(__linux)

// Linux
#define OS_LINUX

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

// Mac OS
#define OS_MAC

#elif defined(__FreeBSD) || defined(__FreeBSD_kernel__)

// FreeBSD
#define OS_FREEBSD

#else

#error This os is not supported by this project.

#endif

#endif // !MOGNETWORK_OS_HH
