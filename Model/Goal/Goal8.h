#ifndef _BUSYBIN_GOAL8_H_
#define _BUSYBIN_GOAL8_H_

#include "Goal.h"
#include "Goal7.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Goal 8 - 2 layers solved except for one corner/edge.  At least 10
   * edeges solved.
   */
  class Goal8 : public Goal
  {
    Goal7 goal7;

  public:
    bool isSatisfied(RubiksCubeModel& cube);
  };
}

#endif

