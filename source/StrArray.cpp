#include "StrArray.h"

StrArray::StrArray(string str, const char delimiter)
{
   uint size = 0, pos = 0;
   while( true )
   {
      string s;

      size = str.find(delimiter, pos);
      if( size == string::npos )
      {
         s = str.substr(pos, string::npos);
      }
      else
      {
         size -= pos;
         s = str.substr(pos, size);
      }

      m_strvec.push_back(s);
      if( size == string::npos ) break;
      pos += size + 1;
   }
}

StrArray::~StrArray() {}

int StrArray::Count()
{
   return m_strvec.size();
}

string& StrArray::operator[](int index)
{
   return m_strvec[index];
}
