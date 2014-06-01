#include "AutoTimer.h"

namespace busybin
{
  /**
   * Start the timer.
   */
  AutoTimer::AutoTimer() : Timer(true)
  {
  }

  /**
   * Report the elapsed time.
   */
  AutoTimer::~AutoTimer()
  {
    cout << "Elapsed time: " << Timer::getElapsedSeconds() << "s" << endl;
  }
}

