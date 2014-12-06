//
// Thread.cpp for Thread in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 17:37:30 2014 Moghrabi Alexandre
// Last update Sat Dec  6 06:17:23 2014 Moghrabi Alexandre
//

#include "mognetwork/OS.hh"

#ifndef OS_WINDOWS

#include <iostream>
#include "mognetwork/Thread.hh"
#include "mognetwork/ThreadException.hh"

namespace mognetwork
{
  Thread::Thread(IRunnable& runnable, bool detach) :
    m_runnable(runnable)
  {
    if (pthread_attr_init(&m_attr) != 0)
      throw ThreadException("pthread_attr_init() error", __LINE__, __FILE__);
    if (detach && pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_DETACHED) != 0)
      throw ThreadException("pthread_attr_setdetachstate error", __LINE__, __FILE__);
    m_started = false;
  }
  
  Thread::~Thread()
  {
    if (pthread_attr_destroy(&m_attr) != 0)
      throw ThreadException("pthread_attr_destroy error", __LINE__, __FILE__);
  }
  
  void Thread::start()
  {
    if (!m_started && pthread_create(&m_thread, &m_attr, &Thread::exec, &m_runnable) != 0)
      throw ThreadException("Thread creation error", __LINE__, __FILE__);
    m_started = true;
  }
  
  void Thread::cancel()
  {
    if (pthread_cancel(m_thread) != 0)
      throw ThreadException("Thread cancel error", __LINE__, __FILE__);
    m_started = false;
  }
  
  void Thread::join()
  {
    if (pthread_join(m_thread, NULL) != 0)
      throw ThreadException("Thread cannot be joined", __LINE__, __FILE__);
    m_started = false;
  }

  void* Thread::exec(void *thr)
  {
    reinterpret_cast<IRunnable*>(thr)->run();
    return (NULL);
  }
} // namespace mognetwork

#endif // OS_LINUX
