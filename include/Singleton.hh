//
// Singleton.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 18:30:59 2014 Moghrabi Alexandre
// Last update Tue Nov 18 13:09:40 2014 Moghrabi Alexandre
//

/*!
 * \file Singleton.hh
 * \brief Simplification de la gestion des Singleton
 * \author AlexMog
 * \version 0.5
 */

#ifndef MOGNETWORK_SINGLETON_HH
# define MOGNETWORK_SINGLETON_HH

namespace mognetwork
{
  /*!
   * \class Singleton
   * \brief Simplification de la gestion des Singleton
   */
  template <class T>
  class Singleton
  {
  public:
    /*!
     * \brief Récupération de l'instance d'un Singleton
     * \return l'instance du Singleton
     */
    static T& Instance() {
      static T _instance;
      return _instance;
    }

  private:
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
  };
} // namepsace mognetwork

#endif // !MOGNETWORK_SINGLETON_HH
