#ifndef _BUSYBIN_GOAL3x3x3_H_
#define _BUSYBIN_GOAL3x3x3_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Solve a 3x3x3 cube.
   */
  class Goal3x3x3 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

