#ifndef _BUSYBIN_GOAL_H_
#define _BUSYBIN_GOAL_H_

#include "../RubiksCube.h"

namespace busybin
{
  /**
   * Base class for cube solution goals.
   */
  class Goal
  {
  public:
    Goal();
    virtual ~Goal();
    virtual bool isSatisfied(const RubiksCube& cube) = 0;
  };
}

#endif

