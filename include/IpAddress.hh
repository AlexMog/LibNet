//
// IpAddress.hh for  in 
// 
// Made by mognetworkhrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Mon Jun  9 16:06:02 2014 mognetworkhrabi Alexandre
// Last update Tue Nov 18 13:11:23 2014 Moghrabi Alexandre
//

/*!
 * \file IpAddress.hh
 * \brief Objet permettant la gestion des addresses IP
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
   * \brief Permet la gestion d'addresses IP
   */
  class IpAddress
  {
  public:
    /*!
     * \brief Constructeur par défaut
     * \param address L'adresse à utiliser
     */
    IpAddress(const std::string& address);
    virtual ~IpAddress();
    
  private:
    /*!
     * \brief Résout l'adresse IP
     */
    void resolve();
    
  public:
    /*!
     * \brief Renvoit la conversion en INT de l'IP
     * \return la conversion de l'ip en int
     */
    int getInt() const;
    
  private:
    std::string m_sAddress; /*!< Addresse en String stockée */
    uint32_t m_address; /*!< Addresse en int stockée */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_IPADDRESS_HH
