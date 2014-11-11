//
// ThreadException.hh for Thread in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 17:48:39 2014 Moghrabi Alexandre
// Last update Tue Nov 11 19:08:13 2014 Moghrabi Alexandre
//

#ifndef THREADEXCEPTION_HH_
# define THREADEXCEPTION_HH_

# include <iostream>
# include "LibNetworkException.hh"

namespace mognetwork
{
  class ThreadException : public LibNetworkException
  {
  public:
    ThreadException(const char* msg, int line, const char *file) : LibNetworkException(msg, line, file) {}
  };
}; // namespace mognetwork 

#endif // !THREADEXCEPTION_HH_
