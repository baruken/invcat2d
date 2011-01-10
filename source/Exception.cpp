#include "Exception.h"

Exception::Exception(string name,
                     string desc,
                     string func,
                     string clas):
m_name(name), m_desc(desc), m_func(func), m_clas(clas)
{
}

Exception::Exception(const Exception& ex)
{
   m_name = ex.m_name;
   m_desc = ex.m_desc;
   m_func = ex.m_func;
   m_clas = ex.m_clas;
}

const char* Exception::Name()
{
    return m_name.c_str();
}

const char* Exception::Description()
{
    return m_desc.c_str();
}

const char* Exception::Function()
{
    return m_func.c_str();
}

const char* Exception::Class()
{
    return m_clas.c_str();
}
