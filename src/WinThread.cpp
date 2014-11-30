//
// Thread.cpp for Thread in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 17:37:30 2014 Moghrabi Alexandre
// Last update Sun Nov 30 16:57:06 2014 Moghrabi Alexandre
//

#include "mognetwork/OS.hh"

#if defined(OS_WINDOWS)

#include <windows.h>
#include "mognetwork/Thread.hh"
#include "mognetwork/ThreadException.hh"

namespace mognetwork
{
  Thread::Thread(IRunnable& runnable, bool detach) :
    m_runnable(runnable)
  {
    (void)detach;
    m_started = false;
  }
  
  Thread::~Thread()
  {
    CloseHandle(m_thread);
  }
  
  void Thread::start()
  {
    if (!m_started && (m_thread = CreateThread(NULL, 0, Thread::exec, &m_runnable, 0, &m_thread)) == NULL)
      throw ThreadException("Thread creation error", __LINE__, __FILE__);
    m_started = true;
  }
  
  void Thread::cancel()
  {
    if (TerminateThread(m_thread, 0) == 0)
      throw ThreadException("Thread cancel error", __LINE__, __FILE__);
    m_started = false;
  }
  
  void Thread::join()
  {
    if (WaitForSingleObject(m_thread, INFINITE) == WAIT_FAILED)
      throw ThreadException("Thread cannot be waited", __LINE__, __FILE__);
    m_started = false;
  }

  DWORD WINAPI Thread::exec(LPVOID thr)
  {
    reinterpret_cast<IRunnable*>(thr)->run();
    return (NULL);
  }
} // namespace mognetwork

#endif // OS_WINDOWS
