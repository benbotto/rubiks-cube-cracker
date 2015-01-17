#ifndef _BUSYBIN_GoalG1_G2_H_
#define _BUSYBIN_GoalG1_G2_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Orient all corners, and place FU, FD, BU, BD in the correct slice.
   */
  class GoalG1_G2 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

