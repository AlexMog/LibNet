//
// Mutex.hh for Mutex in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 19:30:25 2014 Moghrabi Alexandre
// Last update Tue Nov 11 19:47:25 2014 Moghrabi Alexandre
//

#ifndef MUTEX_HH_
# define MUTEX_HH_

# include <pthread.h>

namespace mognetwork
{
  class Mutex
  {
  public:
    Mutex();
    virtual ~Mutex();

  public:
    void lock();
    void unlock();
    void trylock();

  protected:
    pthread_mutex_t m_mutex;
  };
}; // namespace mognetwork

#endif // !MUTEX_HH_
