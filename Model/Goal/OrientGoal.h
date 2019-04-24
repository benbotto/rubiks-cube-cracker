#ifndef _BUSYBIN_ORIENT_GOAL_H_
#define _BUSYBIN_ORIENT_GOAL_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Orient the scambled cube with red on the top and white on the front.
   */
  class OrientGoal : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

