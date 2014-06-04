#ifndef _BUSYBIN_GOAL4_H_
#define _BUSYBIN_GOAL4_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Goal 4 - solve a 2x2x2 cube with two additional solved cubes 
   * with matching color.
   */
  class Goal4 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
  };
}

#endif

