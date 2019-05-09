#ifndef _BUSYBIN_SOLVED_GOAL_H_
#define _BUSYBIN_SOLVED_GOAL_H_

#include "Goal.h"
#include "../RubiksCube.h"
#include <cstdint>

namespace busybin
{
  /**
   * Solve the cube.
   */
  class SolveGoal : public Goal
  {
  public:
    bool isSatisfied(RubiksCube& cube);
    string getDescription() const;
  };
}

#endif

