#ifndef _BUSYBIN_GOAL2x2x2_PLUS_ONE_EDGE_H_
#define _BUSYBIN_GOAL2x2x2_PLUS_ONE_EDGE_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Solve a 2x2x2 cube with an additional edge.
   * with matching color.
   */
  class Goal2x2x2_Plus_One_Edge : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

