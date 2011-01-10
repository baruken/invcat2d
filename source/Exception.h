#ifndef __Exception_h__
#define __Exception_h__

/** Custom exception class.
    Enables collecting data from program errors.
*/

#include <sstream>
#include <string>

#define  EX_OS_API      "Error in OS API call."
#define  EX_SDL         "Error in SDL call."
#define  EX_EXTERNAL    "External error."
#define  EX_INTERNAL    "Internal error."
#define  EX_SPRITE_DEF  "Invalid sprite definition file."

using namespace std;

/** Exception class.
    Defines standard exception requirements for error handling consistency.
    This is the only exception type that should be used by the application
    and should be thrown everytime a fatal error occurs.
*/

class Exception
{
   public:
      /** Default constructor.
          @param name   Exception name. Use and EX_ define that represents best the error.
          @param desc   Exception description. Provide all details of the error.
          @param func   Function where the error occurred.
          @param clas   Class where the error occurred.
      */
      Exception(string name,
                string desc,
                string func,
                string clas);
      /** Copy constructor. For exception propagation. */
      Exception(const Exception& ex);
      ~Exception() {}

      /** Exception name. */
      const char* Name();
      /** Exception detailed description. */
      const char* Description();
      /** Function where exception ocurred. */
      const char* Function();
      /** Class which originally thrown the exception. */
      const char* Class();

   private:
      Exception();
      const Exception& operator=(const Exception& ex);

      string      m_name;
      string      m_desc;
      string      m_func;
      string      m_clas;
};

#endif // __Exception_h__
