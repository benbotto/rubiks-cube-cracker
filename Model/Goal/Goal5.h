#ifndef _BUSYBIN_GOAL5_H_
#define _BUSYBIN_GOAL5_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Goal 5 - solve a 2x2x3 cube.
   */
  class Goal5 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
  };
}

#endif

