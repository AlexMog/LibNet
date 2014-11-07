//
// OS.hh for OS in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Thu Jun  5 18:44:24 2014 mognetworkhrabi Alexandre
// Last update Thu Jun  5 19:12:39 2014 mognetworkhrabi Alexandre
//

#ifndef OS_HH
# define OS_HH

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

#endif // !OS_HH
