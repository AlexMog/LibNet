//
// IpAddress.cpp for  in 
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Mon Jun  9 16:05:21 2014 Moghrabi Alexandre
// Last update Wed Oct  8 07:58:40 2014 Moghrabi Alexandre
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include "IpAddress.hh"

namespace Mog
{
  IpAddress::IpAddress(const std::string& address) : m_sAddress(address), m_address(0) {}
  
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
} // namespace Mog
