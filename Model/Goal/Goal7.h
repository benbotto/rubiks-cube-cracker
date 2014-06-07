#ifndef _BUSYBIN_GOAL7_H_
#define _BUSYBIN_GOAL7_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Goal 7 - 2 layers solved except for one corner/edge.
   */
  class Goal7 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
  };
}

#endif

