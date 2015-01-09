#include "Timer.h"

namespace busybin
{
  /**
   * Initialize the timer.
   * @param start Automatically start the timer.
   */
  Timer::Timer(bool start)
  {
    if (start)
      this->start();
    else
      this->started = false;
  }

  /**
   * Start (or restart) the timer.
   */
  void Timer::start()
  {
    this->startTime = system_clock::now();
    this->started   = true;
  }

  /**
   * Restart the timer (same as start).
   */
  void Timer::restart()
  {
    this->start();
  }

  /**
   * Stop the timer.
   */
  void Timer::stop()
  {
    this->started = false;
  }

  /**
   * Initialize the timer.
   */
  double Timer::getElapsedSeconds() const
  {
    if (!started)
    {
      return 0;
    }
    else
    {
      time_point<system_clock> end = std::chrono::system_clock::now();
      duration<double> secs = end - this->startTime; 

      return secs.count();
    }
  }

  /**
   * Check if the timer is started.
   */
  bool Timer::isStarted() const
  {
    return this->started;
  }
}

