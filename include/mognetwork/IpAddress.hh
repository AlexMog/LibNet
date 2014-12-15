//
// IpAddress.hh for  in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Mon Jun  9 16:06:02 2014 mognetworkhrabi Alexandre
// Last update Mon Dec 15 09:47:05 2014 Moghrabi Alexandre
//

/*!
 * \file IpAddress.hh
 * \brief An Ip converter
 * \author AlexMog
 * \version 0.2
 */

#include <stdint.h>

#ifndef MOGNETWORK_IPADDRESS_HH
# define MOGNETWORK_IPADDRESS_HH

# include <string>

namespace mognetwork
{
  /*!
   * \class IpAddress
   * \brief Simplify the conversion of an IP
   */
  class IpAddress
  {
  public:
    /*!
     * \brief Default constructor
     * \param address The ip address
     */
    IpAddress(const std::string& address);
    virtual ~IpAddress();
    
  private:
    /*!
     * \brief Resolve the ip address
     */
    void resolve();
    
  public:
    /*!
     * \brief Get the int conversion of the ip
     * \return The int conversion of the ip
     */
    int getInt() const;
    
  private:
    std::string m_sAddress; /*!< String address stocked */
    uint32_t m_address; /*!< Int address stocked */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_IPADDRESS_HH
