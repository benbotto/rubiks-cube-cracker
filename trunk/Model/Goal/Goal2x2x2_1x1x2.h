#ifndef _BUSYBIN_GOAL2x2x2_1x1x2_H_
#define _BUSYBIN_GOAL2x2x2_1x1x2_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Solve a 2x2x2 cube with an adjacent 1x1x2.
   * with matching color.
   */
  class Goal2x2x2_1x1x2 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

