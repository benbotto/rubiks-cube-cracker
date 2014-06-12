#ifndef _BUSYBIN_GOAL2x2x3_1x2x2_1x1x2_H_
#define _BUSYBIN_GOAL2x2x3_1x2x2_1x1x2_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Solve a 2x2x3 and 1x2x2, and put a 1x1x2 together.
   */
  class Goal2x2x3_1x2x2_1x1x2 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

