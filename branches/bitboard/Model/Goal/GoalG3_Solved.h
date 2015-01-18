#ifndef _BUSYBIN_GoalG3_Solved_H_
#define _BUSYBIN_GoalG3_Solved_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Solve the cube.
   */
  class GoalG3_Solved : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

