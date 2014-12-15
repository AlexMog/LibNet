//
// ThreadException.hh for Thread in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 17:48:39 2014 Moghrabi Alexandre
// Last update Mon Dec 15 07:06:30 2014 Moghrabi Alexandre
//

/*!
 * \file ThreadException.hh
 * \brief Exception des threads
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_THREADEXCEPTION_HH
# define MOGNETWORK_THREADEXCEPTION_HH

# include <iostream>
# include "LibNetworkException.hh"

namespace mognetwork
{
  /*!
   * \class ThreadException
   * \brief Thread exceptions class
   */
  class ThreadException : public LibNetworkException
  {
  public:
    /*!
     * \brief Default constructor
     * \param msg Error message
     * \param line Line of the error
     * \param file File of the error
     */
    ThreadException(const char* msg, int line, const char *file) : LibNetworkException(msg, line, file) {}
  };
} // namespace mognetwork 

#endif // !MOGNETWORK_THREADEXCEPTION_HH
