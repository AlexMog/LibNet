#ifndef MOGNETWORK_SMARTPTR_HPP
# define MOGNETWORK_SMARTPTR_HPP

namespace mognetwork
{
  template <typename T>
  class SmartPtr
  {
  public:
    SmartPtr() : m_alloc(NULL) {}
    virtual ~SmartPtr() {if (m_alloc != NULL) delete m_alloc;}

  public:
    T* instance() {return m_alloc;}
    void set(T* alloc) {m_alloc = alloc;}

  private:
    T* m_alloc;
  };
}
#endif /* !MOGNETWORK_SMARTPTR_HPP */
