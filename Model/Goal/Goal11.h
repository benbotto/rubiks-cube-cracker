#ifndef _BUSYBIN_GOAL11_H_
#define _BUSYBIN_GOAL11_H_

#include "Goal.h"
#include "Goal7.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Goal 11 - 2 layers solved.
   */
  class Goal11 : public Goal
  {
    Goal7 goal7;

  public:
    bool isSatisfied(RubiksCubeModel& cube);
  };
}

#endif

