#ifndef _BUSYBIN_GOALG0_G1_H_
#define _BUSYBIN_GOALG0_G1_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Orient all edges so that they can be moved home without quarter turns of U
   * or D.
   */
  class GoalG0_G1 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

