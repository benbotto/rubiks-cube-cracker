#ifndef _BUSYBIN_GOAL6_H_
#define _BUSYBIN_GOAL6_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Goal 6 - 2x2x3 cube with an adjacent edge/corner solved.
   */
  class Goal6 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
  };
}

#endif

