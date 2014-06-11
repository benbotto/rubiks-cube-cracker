#ifndef _BUSYBIN_Goal2x2x3_1x1x2_H_
#define _BUSYBIN_Goal2x2x3_1x1x2_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Solve a 2x2x3 cube with an adjacent 1x1x2.
   */
  class Goal2x2x3_1x1x2 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

