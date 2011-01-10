#include "Thread.h"
#include "Exception.h"

Thread::Thread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter):
mp_address(lpStartAddress), mp_parameter(lpParameter)
{
}

Thread::~Thread()
{
}

void Thread::Start()
{
   m_handle = CreateThread(NULL,
                           NULL,
                           mp_address,
                           mp_parameter,
                           0,
                           NULL);
   if( !m_handle )
   {
      stringstream ss;
      ss << "Unable to create thread. Error: " << GetLastError();

      throw Exception(EX_OS_API, ss.str(), "(ctor)", "Thread");
   }
}

void Thread::Kill()
{
   if( TerminateThread(m_handle, 0) == 0 )
   {
      stringstream ss;
      ss << "Unable to kill thread. Error: " << GetLastError();

      throw Exception(EX_OS_API, ss.str(), "Kill", "Thread");
   }
}

void Thread::Wait()
{
   DWORD result = WaitForSingleObject(m_handle, INFINITE);
   if( result == WAIT_FAILED )
   {
      stringstream ss;
      ss << "WaitForSingleObject failed. Error: " << GetLastError();

      throw Exception(EX_OS_API, ss.str(), "Wait", "Thread");
   }
}
