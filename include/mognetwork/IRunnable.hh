//
// IRunnable.hh for libnet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 18:05:43 2014 Moghrabi Alexandre
// Last update Mon Dec 15 09:45:43 2014 Moghrabi Alexandre
//

/*!
 * \file IRunnable.hh
 * \brief Create an execution function for the Thread class
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_IRUNNABLE_HH
# define MOGNETWORK_IRUNNABLE_HH

namespace mognetwork
{
  /*!
   * \class IRunnable
   * \brief Create an execution function for the Thread class
   */
  class IRunnable
  {
  public:
    virtual ~IRunnable() {}
    /*!
     * \brief The function to set, executed by the Thread
     */
    virtual void run() = 0;
  };
} // namesapce mognetwork

#endif // !MOGNETWORK_IRUNNABLE_HH
