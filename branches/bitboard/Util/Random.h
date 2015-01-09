#ifndef _BUSYBIN_RANDOM_H_
#define _BUSYBIN_RANDOM_H_

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;
#include <chrono>
using std::chrono::system_clock;

namespace busybin
{
  /**
   * Helper for generating random ints in a range.
   */
  class Random
  {
    default_random_engine generator;
    uniform_int_distribution<unsigned> dist;

  public:
    Random(unsigned min, unsigned max);
    unsigned next();
  };
}

#endif

