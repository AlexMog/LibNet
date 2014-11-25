//
// Mutex.hh for Mutex in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 19:30:25 2014 Moghrabi Alexandre
// Last update Tue Nov 18 13:10:38 2014 Moghrabi Alexandre
//

/*!
 * \file Mutex.hh
 * \brief Encapsulation des mutex
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_MUTEX_HH
# define MOGNETWORK_MUTEX_HH

# include <pthread.h>

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
    pthread_mutex_t m_mutex; /*!< données de la mutex */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_MUTEX_HH
