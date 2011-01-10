#ifndef __Thread_h__
#define __Thread_h__

#include <windows.h>

class Thread
{
   public:
      Thread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter = 0);
      ~Thread();

      void  Start();
      void  Wait();
      void  Kill();

   private:
      LPTHREAD_START_ROUTINE  mp_address;
      LPVOID                  mp_parameter;
      HANDLE                  m_handle;
};

#endif // __Thread_h__
