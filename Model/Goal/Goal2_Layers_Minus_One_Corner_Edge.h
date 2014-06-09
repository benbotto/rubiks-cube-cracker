#ifndef _BUSYBIN_GOAL2_LAYERS_MINUS_ONE_CORNER_EDGE_H_
#define _BUSYBIN_GOAL2_LAYERS_MINUS_ONE_CORNER_EDGE_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Solve 2 layers except for one corner/edge.
   */
  class Goal2_Layers_Minus_One_Corner_Edge : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

