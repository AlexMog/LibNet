//
// Thread.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 17:31:29 2014 Moghrabi Alexandre
// Last update Tue Nov 18 09:28:50 2014 Moghrabi Alexandre
//

/*!
 * \file Thread.hh
 * \brief Encapsulation des threads
 * \author AlexMog
 * \version 1.0
 */

#ifndef THREAD_HH_
# define THREAD_HH_

# include <pthread.h>
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
    static void* exec(void *);

  public:
    /*!
     * \brief permet de savoir si le thread est actuellement lancé
     * \return true si lancé, sinon false
     */
    bool isStarted() const {return m_started;}

  private:
    IRunnable& m_runnable; /*!< Système de lancement du thread */
    pthread_t m_thread; /*!< identifiant du thread */
    pthread_attr_t m_attr; /*!< configurations du thread */
    bool m_started; /*!< permet de savoir si le thread est actuellement lancé ou non */
  };
} // namespace mognetwork

#endif // !THREAD_HH_
