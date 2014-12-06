//
// Mutex.hh for Mutex in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 19:30:25 2014 Moghrabi Alexandre
// Last update Sat Dec  6 06:19:34 2014 Moghrabi Alexandre
//

/*!
 * \file Mutex.hh
 * \brief Encapsulation des mutex
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_MUTEX_HH
# define MOGNETWORK_MUTEX_HH

#ifndef OS_WINDOWS
# include <pthread.h>
#else
# include <windows.h>
#endif

namespace mognetwork
{
  /*!
   * \class Mutex
   * \brief Encapsulation des Mutex
   */
  class Mutex
  {
  public:
    /*!
     * \brief Constructeur par défaut
     */
    Mutex();
    virtual ~Mutex();

  public:
    /*!
     * \brief block un mutex
     */
    void lock();
    /*!
     * \brief délock un mutex
     */
    void unlock();
    /*!
     * \brief trylock un mutex
     * \return the trylock response
     */
    int trylock();

  protected:
#ifndef OS_WINDOWS
    pthread_mutex_t m_mutex; /*!< données de la mutex */
#else
    HANDLE m_mutex;
#endif
  };
} // namespace mognetwork

#endif // !MOGNETWORK_MUTEX_HH
