//
// LibNetworkException.hh for  in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Tue Nov 11 17:51:02 2014 Moghrabi Alexandre
// Last update Tue Nov 18 13:10:52 2014 Moghrabi Alexandre
//

/*!
 * \file LibNetworkException.hh
 * \brief Exception générique de la lib
 * \author AlexMog
 * \version 1.0
 */

#ifndef MOGNETWORK_LIBNETWORKEXCEPTION_HH
# define MOGNETWORK_LIBNETWORKEXCEPTION_HH

# include <exception>
# include <iostream>
# include <sstream>

namespace mognetwork
{
  /*!
   * \class LibNetworkException
   * \brief Exception générique de la lib
   */
  class LibNetworkException : public std::exception
  {
  public:
    /*!
     * \brief Constructeur par défaut
     * \param msg Définit le message de l'exception
     * \param line Définit la ligne de l'exception. Généralement __LINE__
     * \param file Définit le fichier de l'exception. Généralement __FILE__
     */
    LibNetworkException(const char* msg, int line, const char *file)
    {
      std::ostringstream oss;

      oss << "Error on line " << line << " in file '" << file << "' : " << msg << std::endl;
      this->msg = oss.str();
    }
    virtual ~LibNetworkException() throw() {}

    /*!
     * \brief Permet de récupérer le message d'erreur de l'exception
     * \return le message d'erreur
     */
    virtual const char* what() const throw()
    {
      return this->msg.c_str();
    }
    
  private:
    std::string msg; /*!< Message d'erreur de l'exception */
  };
} // namespace mognetwork
#endif // !MOGNETWORK_LIBNETWORKEXCEPTION_HH
