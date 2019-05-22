#include "Random.h"

namespace busybin
{
  /**
   * Initialize an instance for geterating numbers in the range [min, max] (both inclusive).
   * @param min The minimum random number.
   * @param max The maximum random number.
   */
  Random::Random(unsigned min, unsigned max) : dist(min, max)
  {
    this->generator.seed(system_clock::now().time_since_epoch().count());
  }

  /**
   * Get the next int.
   */
  unsigned Random::next()
  {
    return this->dist(this->generator);
  }
}

