//
// IRunnable.hh for libnet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 18:05:43 2014 Moghrabi Alexandre
// Last update Wed Nov 12 14:56:31 2014 Moghrabi Alexandre
//

/*!
 * \file IRunnable.hh
 * \brief Interface permettant de créer une fonction d'exécution pour les Threads (java style)
 * \author AlexMog
 * \version 1.0
 */

#ifndef IRUNNABLE_HH_
# define IRUNNABLE_HH_

namespace mognetwork
{
  /*!
   * \class IRunnable
   * \brief Interface permettant de créer une fonction d'exécution pour les Threads (java style)
   */
  class IRunnable
  {
  public:
    /*!
     * \brief fonction utilisée par les threads en temps que pointeur sur fonction
     */
    virtual void run() = 0;
  };
}; // namesapce mognetwork

#endif // !IRUNNABLE_HH_
