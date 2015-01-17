#ifndef _BUSYBIN_GoalG2_G3_H_
#define _BUSYBIN_GoalG2_G3_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Get all edges in the correct slice and all corners in the correct orbit.
   */
  class GoalG2_G3 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

