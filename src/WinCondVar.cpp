//
// CondVar.cpp for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 19:48:17 2014 Moghrabi Alexandre
// Last update Sat Dec  6 06:53:09 2014 Moghrabi Alexandre
//

#include "mognetwork/ThreadException.hh"
#include "mognetwork/CondVar.hh"

#if defined OS_WINDOWS

namespace mognetwork
{
  CondVar::CondVar()
  {
    InitializeConditionVariable(&m_cond);
    InitializeSRWLock(&m_lock);
  }

  CondVar::~CondVar()
  {
    WakeAllConditionVariable(&m_cond);
  }

  void CondVar::wait()
  {
    if (CONDITION_VARIABLE_LOCKMODE_SHARED(&m_cond, &m_lock, INFINITE, CONDITION_VARIABLE_LOCKMODE_SHARED) == 0)
      throw ThreadException("pthread_cond_wait error.", __LINE__, __FILE__);
  }

  void CondVar::signal()
  {
    WakeConditionVariable(&m_cond);
  }

  void CondVar::broadcast()
  {
    WakeAllConditionVariable(&m_cond);
  }

  void CondVar::timedwait(const struct timespec* abstime)
  {
    (void)abstime;
  }
} // namespace mognetwork

#endif // OS_WINDOWS
