#ifndef _BUSYBIN_ORIENT2x2x3_1x1x2_H_
#define _BUSYBIN_ORIENT2x2x3_1x1x2_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Orient a 2x2x3 cube with an adjacent 1x1x2.
   * The 2x2x3 is in the back, and the 1x1x2 is in the front.
   */
  class Orient2x2x3_1x1x2 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

