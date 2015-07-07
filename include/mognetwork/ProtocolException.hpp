//
// LibNetworkException.hh for  in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 17:51:02 2014 Moghrabi Alexandre
// Last update Tue Jul  7 16:28:29 2015 Moghrabi Alexandre
//

/*!
 * \file ProtocolException.hh
 * \brief Protocol Exception
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_PROTOCOLEXCEPTION_HH
# define MOGNETWORK_PROTOCOLEXCEPTION_HH

# include <errno.h>
# include <string.h>
# include <exception>
# include <iostream>
# include <sstream>
# include "LibNetworkException.hh"

namespace mognetwork
{
  /*!
   * \class ProtocolException
   * \brief LibNet protocol exceptions
   */
  class ProtocolException : public LibNetworkException
  {
  public:
    /*!
     * \brief Default constructor
     * \param msg Error message
     * \param line Line of the error. Usually __LINE__
     * \param file File of the error. Usually __FILE__
     * \param func optionnal: __FUNC__
     */
    ProtocolException(const char* msg, int line, const char *file, const char* func = "")
      : LibNetworkException(msg, line, file, func) {}
    virtual ~ProtocolException() throw() {}
  };
} // namespace mognetwork
#endif // !MOGNETWORK_PROTOCOLEXCEPTION_HH
