#ifndef _BUSYBIN_GOALG2_G3_EDGES_H_
#define _BUSYBIN_GOALG2_G3_EDGES_H_

#include "Goal.h"
#include "GoalG3_Permute_Corners.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Get all edges in the correct slice so that they can be solved with only
   * 180-degree turns.
   */
  class GoalG2_G3_Edges : public Goal
  {
    GoalG3_Permute_Corners perms;

  public:
    GoalG2_G3_Edges(GoalG3_Permute_Corners& perms);
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

