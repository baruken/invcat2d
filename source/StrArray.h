#ifndef __Utilities_h__
#define __Utilities_h__

#include "Types.h"
#include <vector>
#include <string>

using namespace std;


/** StrArray class: holds an array of std strings.
    Split one string into an array of strings, using the 'delimiter' character as reference.
 */
class StrArray
{
   public:
      StrArray(string str, const char delimiter);
      ~StrArray();

      /** Returns a string reference to the informed index.
          Beware that an attempt to access an invalid item will result in an exception
          and terminate the application.
      */
      string& operator[](int index);
      /** Return the substring count (index range). */
      int Count();

   private:
      vector<string> m_strvec;
};

#endif // __Utilities_h__
