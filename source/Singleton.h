#ifndef __Singleton_h__
#define __Singleton_h__

#include "Exception.h"

template<class T>
class SingletonDestroyer;

/** Singleton template.
    Implements the Singleton design pattern.
*/
template<class T>
class Singleton
{
public:
   /** Returns the instance of the singleton. */
   static T& Instance()
   {
      if( !mp_instance )
      {
         try
         {
            mp_instance = new T;
         }
         catch(Exception& e)
         {
            throw;
         }

         m_destroyer.SetSingleton(mp_instance);
      }

      return *mp_instance;
   }

protected:
   /* No constructor is available. The singleton design pattern
      doesn't allow the creation of multiple instances of an object. */
   Singleton() {}
   Singleton(const Singleton&) {}
   ~Singleton() {}
   const Singleton& operator=(const Singleton&) { return *this; }

   friend class SingletonDestroyer<T>;

private:
   /** The class instance */
   static T* mp_instance;
   static SingletonDestroyer<T> m_destroyer;

};

template<class T> T* Singleton<T>::mp_instance = 0;
template<class T> SingletonDestroyer<T> Singleton<T>::m_destroyer;

template<class T>
class SingletonDestroyer
{
   public:
      SingletonDestroyer(T* s = 0)
      {
         _singleton = s;
      }

      ~SingletonDestroyer()
      {
         delete _singleton;
      }

      void SetSingleton(T* s)
      {
         _singleton = s;
      }

private:
      T* _singleton;
};


#endif // __Singleton_h__
