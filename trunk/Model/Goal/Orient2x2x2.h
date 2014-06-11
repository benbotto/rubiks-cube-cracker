#ifndef _BUSYBIN_ORIENT2x2x2_H_
#define _BUSYBIN_ORIENT2x2x2_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Orient the 2x2x2 cube at the front, bottom, left.
   */
  class Orient2x2x2 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

