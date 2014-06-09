#ifndef _BUSYBIN_GOAL9_H_
#define _BUSYBIN_GOAL9_H_

#include "Goal.h"
#include "Goal7.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Goal 9 - 2 layers solved except for one corner/edge.  All edges solved.
   */
  class Goal9 : public Goal
  {
    Goal7 goal7;

  public:
    bool isSatisfied(RubiksCubeModel& cube);
  };
}

#endif

