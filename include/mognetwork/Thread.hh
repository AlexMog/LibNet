//
// Thread.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 17:31:29 2014 Moghrabi Alexandre
// Last update Mon Dec 15 07:06:03 2014 Moghrabi Alexandre
//

/*!
 * \file Thread.hh
 * \brief thread encapsulation
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_THREAD_HH
# define MOGNETWORK_THREAD_HH

# include "OS.hh"

#ifndef OS_WINDOWS
# include <pthread.h>
#else
# include <windows.h>
#endif
# include "IRunnable.hh"

namespace mognetwork
{
  /*!
   * \class Thread
   * \brief Encapsulation of thread
   */
  class Thread
  {
  public:
    /*!
     * \brief Constructor
     * \param runnable The runnable to use with the thread
     * \param detach True if you want to detach the thread
     */
    Thread(IRunnable& runnable, bool detach);
    virtual ~Thread();

  public:
    /*!
     * \brief Launch the thread
     */
    virtual void start();
    /*!
     * \brief Cancel the thread
     */
    virtual void cancel();
    /*!
     * \brief Wait to the end of the thread
     */
    virtual void join();

  protected:
    /*!
     * \brief Used to set a function-pointer to threads
     */
#ifndef OS_WINDOWS
    static void* exec(void *);
#else
    static DWORD WINAPI exec(LPVOID);
#endif // OS_WINDOWS

  public:
    /*!
     * \brief Used to know if the thread is launched
     * \return true if launched, false if stopped
     */
    bool isStarted() const {return m_started;}

  private:
    IRunnable& m_runnable; /*!< The runnable used to the thread execution */
#ifndef OS_WINDOWS
    pthread_t m_thread; /*!< Thread identification */
    pthread_attr_t m_attr; /*!< thread configuration */
#else
    HANDLE m_thread;
#endif // OS_WINDOWS
    bool m_started; /*!< used to know if the thread is launched */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_THREAD_HH
