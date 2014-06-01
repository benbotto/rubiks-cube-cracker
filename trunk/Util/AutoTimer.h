#ifndef _BUSYBIN_AUTO_TIMER_H_
#define _BUSYBIN_AUTO_TIMER_H_

#include  "Timer.h"

#include <iostream>
using std::cout;
using std::endl;

namespace busybin
{
  /**
   * Automatic timer that reports time on destruct.
   */
  class AutoTimer : public Timer
  {
  public:
    AutoTimer();
    ~AutoTimer();
  };
}

#endif

