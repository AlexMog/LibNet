//
// Thread.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 17:31:29 2014 Moghrabi Alexandre
// Last update Sun Nov 30 16:54:50 2014 Moghrabi Alexandre
//

/*!
 * \file Thread.hh
 * \brief Encapsulation des threads
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_THREAD_HH
# define MOGNETWORK_THREAD_HH

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
   * \brief Classe d'encapsulation des threads
   */
  class Thread
  {
  public:
    /*!
     * \brief Constructeur
     * \param runnable Un runnable pour le lancement du thread
     * \param detach Le thread est il attaché?
     */
    Thread(IRunnable& runnable, bool detach);
    virtual ~Thread();

  public:
    /*!
     * \brief Lance le thread
     */
    virtual void start();
    /*!
     * \brief Annule le thread
     */
    virtual void cancel();
    /*!
     * \brief Attend que le thread se termine
     */
    virtual void join();

  protected:
    /*!
     * \brief Utilisée pour passer un pointeur sur fonction au thread
     */
#ifndef OS_WINDOWS
    static void* exec(void *);
#else
    static DWORD WINAPI exec(LPVOID);
#endif // OS_WINDOWS

  public:
    /*!
     * \brief permet de savoir si le thread est actuellement lancé
     * \return true si lancé, sinon false
     */
    bool isStarted() const {return m_started;}

  private:
    IRunnable& m_runnable; /*!< Système de lancement du thread */
#ifndef OS_WINDOWS
    pthread_t m_thread; /*!< identifiant du thread */
    pthread_attr_t m_attr; /*!< configurations du thread */
#else
    HANDLE m_thread;
#endif // OS_WINDOWS
    bool m_started; /*!< permet de savoir si le thread est actuellement lancé ou non */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_THREAD_HH
