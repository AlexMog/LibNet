//
// IpAddress.hh for  in 
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Mon Jun  9 16:06:02 2014 Moghrabi Alexandre
// Last update Wed Oct  8 07:56:15 2014 Moghrabi Alexandre
//

#include <stdint.h>

#ifndef IPADDRESS_HH
# define IPADDRESS_HH

# include <string>

namespace Mog
{
class IpAddress
{
public:
  IpAddress(const std::string& address);
  virtual ~IpAddress();

private:
  void resolve();

public:
  int getInt() const;

private:
  std::string m_sAddress;
  uint32_t m_address;
};
} // namespace Mog

#endif // !IPADDRESS_HH
