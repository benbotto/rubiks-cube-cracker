#include "Random.h"

namespace busybin
{
  /**
   * Init.
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

