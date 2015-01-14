#ifndef _BUSYBIN_GOALG0_ORIENT_EDGES_H_
#define _BUSYBIN_GOALG0_ORIENT_EDGES_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Orient all edges so that they can be moved home without quarter turns of U
   * or D.
   */
  class GoalG0_orient_edges : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

