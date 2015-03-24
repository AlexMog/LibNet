//
// IpAddress.cpp for  in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Mon Jun  9 16:05:21 2014 mognetworkhrabi Alexandre
// Last update Tue Mar 24 19:40:41 2015 Moghrabi Alexandre
//

#include "mognetwork/OS.hh"
#ifndef OS_WINDOWS
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#else
#include <winsock2.h>
#include <Ws2tcpip.h>
#endif // !OS_WINDOWS
#include <sys/types.h>
#include <string.h>
#include "mognetwork/IpAddress.hh"

namespace mognetwork
{
  IpAddress::IpAddress(const std::string& address) :
    m_sAddress(address),
    m_address(0)
  {
    resolve();
  }
  
  IpAddress::~IpAddress() {}

  // Extracted from the SFML2.1 sourcecode
  void IpAddress::resolve()
  {
    if (m_sAddress == "255.255.255.255")
      m_address = INADDR_BROADCAST;
    else
      {
	uint32_t ip = inet_addr(m_sAddress.c_str());
	if (ip != INADDR_NONE)
	  m_address = ip;
	else
	  {
	    addrinfo hints;
	    memset(&hints, 0, sizeof(hints));
	    hints.ai_family = AF_INET;
	    addrinfo* result = NULL;
	    if (getaddrinfo(m_sAddress.c_str(), NULL, &hints, &result) == 0)
	      {
		if (result)
		  {
		    ip = reinterpret_cast<sockaddr_in*>(result->ai_addr)->sin_addr.s_addr;
		    freeaddrinfo(result);
		    m_address = ip;
		  }
	      }
	  }
      }
  }

  int IpAddress::getInt() const
  {
    return (ntohl(m_address));
  }
} // namespace mognetwork
