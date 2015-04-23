//
// CondVar.cpp for LibNet in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 19:48:17 2014 Moghrabi Alexandre
// Last update Thu Dec 11 17:22:56 2014 Moghrabi Alexandre
//

#include "mognetwork/OS.hh"

#if defined OS_WINDOWS
#include "mognetwork/ThreadException.hh"
#include "mognetwork/CondVar.hh"
#include <iostream>

namespace mognetwork
{
  CondVar::CondVar()
  {
	InitializeConditionVariable(&m_cond);
	InitializeCriticalSection(&m_cSection);
  }

  CondVar::~CondVar()
  {
    WakeAllConditionVariable(&m_cond);
	DeleteCriticalSection(&m_cSection);
  }

  void CondVar::wait()
  {
	  EnterCriticalSection(&m_cSection);
	  if (SleepConditionVariableCS(&m_cond, &m_cSection, INFINITE) == 0)
		throw ThreadException("pthread_cond_wait error.", __LINE__, __FILE__);
	  LeaveCriticalSection(&m_cSection);
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
