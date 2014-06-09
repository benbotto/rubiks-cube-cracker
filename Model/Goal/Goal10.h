#ifndef _BUSYBIN_GOAL10_H_
#define _BUSYBIN_GOAL10_H_

#include "Goal.h"
#include "Goal7.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Goal 10 - 2 layers solved.  All edges solved.
   */
  class Goal10 : public Goal
  {
    Goal7 goal7;

  public:
    bool isSatisfied(RubiksCubeModel& cube);
  };
}

#endif

