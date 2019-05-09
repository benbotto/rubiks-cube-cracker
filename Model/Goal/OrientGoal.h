#ifndef _BUSYBIN_ORIENT_GOAL_H_
#define _BUSYBIN_ORIENT_GOAL_H_

#include "Goal.h"
#include "../RubiksCube.h"

namespace busybin
{
  /**
   * Orient the scambled cube with red on the top and white on the front.
   */
  class OrientGoal : public Goal
  {
  public:
    bool isSatisfied(RubiksCube& cube);
    string getDescription() const;
  };
}

#endif

