//
// CondVar.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 19:43:06 2014 Moghrabi Alexandre
// Last update Tue Nov 11 19:49:16 2014 Moghrabi Alexandre
//

#ifndef CONDVAR_HH_
# define CONDVAR_HH_

# include <pthread.h>
# include "Mutex.hh"

namespace mognetwork
{
  class CondVar : public Mutex
  {
  public:
    CondVar();
    virtual ~CondVar();

  public:
    void wait();
    void signal();
    void broadcast();
    void timedwait(const struct timespec* abstime);

  protected:
    pthread_cond_t m_cond;
  };
}; // namespace mognetwork

#endif // !CONDVAR_HH_
