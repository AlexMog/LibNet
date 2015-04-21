//
// CondVar.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 19:43:06 2014 Moghrabi Alexandre
// Last update Tue Apr 21 10:33:39 2015 Moghrabi Alexandre
//

/*!
 * \file CondVar.hh
 * \brief Conditional variables encapsulation.
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_CONDVAR_HH
# define MOGNETWORK_CONDVAR_HH

# include "OS.hh"

#ifndef OS_WINDOWS
# include <pthread.h>
#else
# define _WIN32_WINNT 0x0600
# define WINVER 0x0600
# include <windows.h>
#endif // !OS_WINDOWS
# include "Mutex.hh"

namespace mognetwork
{
  /*!
   * \class CondVar
   * \brief Conditional Variables encapsulation
   */
  class CondVar
#ifndef OS_WINDOWS
    : public Mutex
#endif
  {
  public:
    /*!
     * \brief Default constructor
     */
    CondVar();
    virtual ~CondVar();

  public:
    /*!
     * \brief Wait for a signal on the CondVar
     */
    void wait();
    /*!
     * \brief send a signal to the CondVar
     */
    void signal();
    /*!
     * \brief send a signal to all the Threads that uses the CondVar
     */
    void broadcast();
    /*
     * \brief Wait for a signal with a timeout
     * \param abstime Timeout value
     */
    void timedwait(const struct timespec* abstime);

  protected:
#ifndef OS_WINDOWS
    pthread_cond_t m_cond; /*!< CondVar datas */
#else
    CONDITION_VARIABLE m_cond;
    PSRWLOCK m_lock;
#endif // !OS_WINDOWS
  };
} // namespace mognetwork

#endif // !MOGNETWORK_CONDVAR_HH
