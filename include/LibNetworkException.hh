//
// LibNetworkException.hh for  in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 17:51:02 2014 Moghrabi Alexandre
// Last update Tue Nov 11 19:06:53 2014 Moghrabi Alexandre
//

#ifndef LIBNETWORKEXCEPTION_HH_
# define LIBNETWORKEXCEPTION_HH_

# include <exception>
# include <iostream>
# include <sstream>

namespace mognetwork
{
  class LibNetworkException : public std::exception
  {
  public:
    LibNetworkException(const char* msg, int line, const char *file)
    {
      std::ostringstream oss;

      oss << "Error on line " << line << " in file '" << file << "' : " << msg << std::endl;
      this->msg = oss.str();
    }
    virtual ~LibNetworkException() throw() {}

    virtual const char* what() const throw()
    {
      return this->msg.c_str();
    }
    
  private:
    std::string msg;
  };
}; // namespace mognetwork
#endif // !LIBNETWORKEXCEPTION_HH_
