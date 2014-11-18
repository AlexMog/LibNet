//
// Mutex.cpp for Mutex in /home/alexmog/projets/LibNet/src
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 19:36:19 2014 Moghrabi Alexandre
// Last update Tue Nov 18 09:31:01 2014 Moghrabi Alexandre
//

#include "ThreadException.hh"
#include "Mutex.hh"

namespace mognetwork
{
  Mutex::Mutex()
  {
    if (pthread_mutex_init(&m_mutex, NULL) != 0)
      throw ThreadException("pthread_mutex_init error", __LINE__, __FILE__);
  }

  Mutex::~Mutex()
  {
    if (pthread_mutex_destroy(&m_mutex) != 0)
      throw ThreadException("pthread_mutex_destroy error", __LINE__, __FILE__);
  }

  void Mutex::lock()
  {
    if (pthread_mutex_lock(&m_mutex) != 0)
      throw ThreadException("pthread_mutex_lock error", __LINE__, __FILE__);
  }

  void Mutex::unlock()
  {
    if (pthread_mutex_unlock(&m_mutex) != 0)
      throw ThreadException("pthread_mutex_unlock error", __LINE__, __FILE__);
  }

  int Mutex::trylock()
  {
    return pthread_mutex_trylock(&m_mutex);
  }
} // namepsace mognetwork
