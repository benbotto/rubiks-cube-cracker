#ifndef _BUSYBIN_GOAL2x2x3_H_
#define _BUSYBIN_GOAL2x2x3_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Solve a 2x2x3 cube.
   */
  class Goal2x2x3 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

