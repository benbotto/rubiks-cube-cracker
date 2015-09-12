#ifndef _BUSYBIN_GOALG2_G3_CORNERS_H_
#define _BUSYBIN_GOALG2_G3_CORNERS_H_

#include "Goal.h"
#include "GoalG3_Permute_Corners.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Get all corners in their correct orbit such that they can be solved with
   * only 180-degree turns.
   */
  class GoalG2_G3_Corners : public Goal
  {
    GoalG3_Permute_Corners perms;

  public:
    GoalG2_G3_Corners(GoalG3_Permute_Corners& perms);
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

