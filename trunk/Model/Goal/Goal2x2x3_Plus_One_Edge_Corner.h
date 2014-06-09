#ifndef _BUSYBIN_Goal2x2x3_PLUS_ONE_EDGE_CORNER_H_
#define _BUSYBIN_Goal2x2x3_PLUS_ONE_EDGE_CORNER_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Solve a 2x2x3 cube with an adjacent edge/corner solved.
   */
  class Goal2x2x3_Plus_One_Edge_Corner : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

