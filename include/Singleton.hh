//
// Singleton.hh for LibNet in /home/alexmog/projets/LibNet/include
// 
// Made by Moghrabi Alexandre
// Login   <alexandre.moghrabi@epitech.eu>
// 
// Started on  Wed Nov 12 18:30:59 2014 Moghrabi Alexandre
// Last update Wed Nov 12 18:33:04 2014 Moghrabi Alexandre
//

#ifndef SINGLETON_HH_
# define SINGLETON_HH_

namespace mognetwork
{
  template <class T>
  class Singleton
  {
  public:
    static T& Instance() {
      static T _instance;
      return _instance;
    }

  private:
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
  };
}; // namepsace mognetwork

#endif // !SINGLETON_HH_
