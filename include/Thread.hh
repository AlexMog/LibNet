//
// Thread.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 17:31:29 2014 Moghrabi Alexandre
// Last update Tue Nov 11 19:49:59 2014 Moghrabi Alexandre
//

#ifndef THREAD_HH_
# define THREAD_HH_

# include <pthread.h>
# include "IRunnable.hh"

namespace mognetwork
{
  class Thread
  {
  public:
    Thread(IRunnable& runnable, bool detach);
    ~Thread();

  public:
    virtual void start();
    virtual void cancel();
    virtual void join();

  protected:
    static void* exec(void *);

  private:
    IRunnable& m_runnable;
    pthread_t m_thread;
    pthread_attr_t m_attr;
    bool m_started;
  };
}; // namespace mognetwork

#endif // !THREAD_HH_
