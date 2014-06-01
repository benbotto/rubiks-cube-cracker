#ifndef _BUSYBIN_ITERABLE_H_
#define _BUSYBIN_ITERABLE_H_

#include "Iterator.h"

namespace busybin
{
  /**
   * Interface for iterable collections.
   */
  template <class T>
  class Iterable
  {
  public:
    virtual T& at(unsigned) = 0;
    virtual const T& at(unsigned) const = 0;

    virtual Iterator<T> begin() = 0;
    virtual ConstIterator<T> begin() const = 0;

    virtual Iterator<T> end() = 0;
    virtual ConstIterator<T> end() const = 0;
  };
}

#endif

