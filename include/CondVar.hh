//
// CondVar.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 19:43:06 2014 Moghrabi Alexandre
// Last update Tue Nov 18 13:11:35 2014 Moghrabi Alexandre
//

/*!
 * \file CondVar.hh
 * \brief Encapsulation des variables conditionnelles
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_CONDVAR_HH
# define MOGNETWORK_CONDVAR_HH

# include <pthread.h>
# include "Mutex.hh"

namespace mognetwork
{
  /*!
   * \class CondVar
   * \brief Encapsulation des variables conditionnelles
   */
  class CondVar : public Mutex
  {
  public:
    /*!
     * \brief Constructeur par défaut
     */
    CondVar();
    virtual ~CondVar();

  public:
    /*!
     * \brief Attend que la condVar soit notifiée
     */
    void wait();
    /*!
     * \brief notifie la condVar
     */
    void signal();
    /*!
     * \brief signal tous les threads contenant cette condVar
     */
    void broadcast();
    /*
     * \brief Attend que la condVar soit notifiée avec un temps limite
     * \param abstime temps limite
     */
    void timedwait(const struct timespec* abstime);

  protected:
    pthread_cond_t m_cond; /*!< Variable conditionnelle */
  };
} // namespace mognetwork

#endif // !MOGNETWORK_CONDVAR_HH
