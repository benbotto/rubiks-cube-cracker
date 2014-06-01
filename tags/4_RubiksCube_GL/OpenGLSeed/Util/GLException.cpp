#include "GLException.h"

namespace busybin
{
  /**
   * Ctor from const char.
   * @param what The message.
   */
  GLException::GLException(const char* const what)
  {
    this->msg = what;
  }

  /**
   * Ctor from string.
   * @param what The message.
   */
  GLException::GLException(const string& what)
  {
    this->msg = what;
  }

  /**
   * Get the exception message.
   */
  const char* GLException::what() const throw()
  {
    return this->msg.c_str();
  }

  /**
   * Do-nothing deconstructor.
   */
  GLException::~GLException() throw() {}
}

