//
// IRunnable.hh for libnet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 18:05:43 2014 Moghrabi Alexandre
// Last update Tue Nov 11 19:08:32 2014 Moghrabi Alexandre
//

#ifndef IRUNNABLE_HH_
# define IRUNNABLE_HH_

namespace mognetwork
{
  class IRunnable
  {
  public:
    virtual void* run() = 0;
  };
}; // namesapce mognetwork

#endif // !IRUNNABLE_HH_
