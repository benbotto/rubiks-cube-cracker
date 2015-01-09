#ifndef _BUSYBIN_GOAL2x3x3_H_
#define _BUSYBIN_GOAL2x3x3_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Solve a 2x3x3 on the bottom.
   */
  class Goal2x3x3 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

