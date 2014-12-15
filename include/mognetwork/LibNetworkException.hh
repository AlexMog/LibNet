//
// LibNetworkException.hh for  in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 17:51:02 2014 Moghrabi Alexandre
// Last update Mon Dec 15 09:42:13 2014 Moghrabi Alexandre
//

/*!
 * \file LibNetworkException.hh
 * \brief Exception générique de la lib
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_LIBNETWORKEXCEPTION_HH
# define MOGNETWORK_LIBNETWORKEXCEPTION_HH

# include <errno.h>
# include <string.h>
# include <exception>
# include <iostream>
# include <sstream>

namespace mognetwork
{
  /*!
   * \class LibNetworkException
   * \brief LibNet exceptions
   */
  class LibNetworkException : public std::exception
  {
  public:
    /*!
     * \brief Default constructor
     * \param msg Error message
     * \param line Line of the error. Usually __LINE__
     * \param file File of the error. Usually __FILE__
     */
    LibNetworkException(const char* msg, int line, const char *file)
    {
      std::ostringstream oss;

      oss << "Error on line " << line << " in file '" << file << "' : " << msg << std::endl
	  << "\tErrno status: " << strerror(errno) << std::endl;
      this->msg = oss.str();
    }
    virtual ~LibNetworkException() throw() {}

    /*!
     * \brief Get the error message
     * \return The error message
     */
    virtual const char* what() const throw()
    {
      return this->msg.c_str();
    }
    
  private:
    std::string msg; /*!< Error message */
  };
} // namespace mognetwork
#endif // !MOGNETWORK_LIBNETWORKEXCEPTION_HH
