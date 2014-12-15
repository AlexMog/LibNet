//
// Singleton.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 18:30:59 2014 Moghrabi Alexandre
// Last update Mon Dec 15 07:39:02 2014 Moghrabi Alexandre
//

/*!
 * \file Singleton.hh
 * \brief Simplification of the Singleton usage
 * \author AlexMog
 * \version 0.5
 */

#ifndef MOGNETWORK_SINGLETON_HH
# define MOGNETWORK_SINGLETON_HH

namespace mognetwork
{
  /*!
   * \class Singleton
   * \brief Simplification of the Singleton usage
   */
  template <class T>
  class Singleton
  {
  public:
    /*!
     * \brief Get the instance of a Singleton
     * \return The Singleton instance
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
