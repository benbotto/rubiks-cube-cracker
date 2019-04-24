#ifndef _BUSYBIN_SOLVED_GOAL_H_
#define _BUSYBIN_SOLVED_GOAL_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"
#include <cstdint>

namespace busybin
{
  /**
   * Solve the cube.
   */
  class SolveGoal : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

