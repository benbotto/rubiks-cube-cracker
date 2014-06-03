#ifndef _BUSYBIN_TIMER_H_
#define _BUSYBIN_TIMER_H_

#include <chrono>
using std::chrono::time_point;
using std::chrono::system_clock;
using std::chrono::duration;

namespace busybin
{
  /**
   * Basic timer.
   */
  class Timer
  {
    bool started;
    time_point<system_clock> startTime;

  public:
    Timer(bool start);
    void start();
    void restart();
    void stop();
    double getElapsedSeconds() const;
    bool isStarted() const;
  };
}

#endif

