//
// Mutex.cpp for Mutex in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 19:36:19 2014 Moghrabi Alexandre
// Last update Sat Dec  6 06:27:07 2014 Moghrabi Alexandre
//

#include "mognetwork/ThreadException.hh"
#include "mognetwork/Mutex.hh"

#if defined(OS_WINDOWS)

namespace mognetwork
{
  Mutex::Mutex()
  {
    if ((m_mutex = CreateMutex(NULL, FALSE, NULL)) == NULL)
      throw ThreadException("pthread_mutex_init error", __LINE__, __FILE__);
  }

  Mutex::~Mutex()
  {
    CloseHandle(m_mutex);
  }

  void Mutex::lock()
  {
    if (WaitForSingleObject(m_mutex, INFINITE) == WAIT_FAILED)
      throw ThreadException("pthread_mutex_lock error", __LINE__, __FILE__);
  }

  void Mutex::unlock()
  {
    if (!ReleaseMutex(m_mutex))
      throw ThreadException("pthread_mutex_unlock error", __LINE__, __FILE__);
  }

  int Mutex::trylock()
  {
    if (WaitForSingleObject(m_mutex, 0) == WAIT_FAILED)
      throw ThreadException("pthread_mutex_lock error", __LINE__, __FILE__);
    return (0);
  }
} // namepsace mognetwork

#endif // !OS_WINDOWS
