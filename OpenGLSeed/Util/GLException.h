#ifndef _BUSYBIN_GL_EXCEPTION_H_
#define _BUSYBIN_GL_EXCEPTION_H_

#include <exception>
using std::exception;
#include <string>
using std::string;

namespace busybin
{
  class GLException : public exception
  {
    string msg;

    GLException();
  public:
    GLException(const char* const what);
    GLException(const string& what);
    virtual const char* what() const throw();
    virtual ~GLException() throw();
  };
}

#endif

