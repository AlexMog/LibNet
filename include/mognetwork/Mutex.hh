//
// Mutex.hh for Mutex in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 19:30:25 2014 Moghrabi Alexandre
// Last update Mon Dec 15 09:41:11 2014 Moghrabi Alexandre
//

/*!
 * \file Mutex.hh
 * \brief Mutex encapsulation
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_MUTEX_HH
# define MOGNETWORK_MUTEX_HH

# include "OS.hh"

#ifndef OS_WINDOWS
# include <pthread.h>
#else
# include <windows.h>
#endif

namespace mognetwork
{
  /*!
   * \class Mutex
   * \brief Mutex encapsulation
   */
  class Mutex
  {
  public:
    /*!
     * \brief Default constructor
     */
    Mutex();
    virtual ~Mutex();

  public:
    /*!
     * \brief lock a Mutex
     */
    void lock();
    /*!
     * \brief Unlock a Mutex
     */
    void unlock();
    /*!
     * \brief Trylock on a Mutex (verify if the mutex can be locked and locks it without blocking
     * \return the trylock response
     */
    int trylock();

  protected:
#ifndef OS_WINDOWS
    pthread_mutex_t m_mutex; /*!< mutex datas */
#else
    HANDLE m_mutex;
#endif
  };
} // namespace mognetwork

#endif // !MOGNETWORK_MUTEX_HH
