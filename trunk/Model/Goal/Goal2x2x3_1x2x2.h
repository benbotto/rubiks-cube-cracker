#ifndef _BUSYBIN_GOAL2x2x3_1x2x2_H_
#define _BUSYBIN_GOAL2x2x3_1x2x2_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Solve 2 layers and an adjacent 1x2x2.
   */
  class Goal2x2x3_1x2x2 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

