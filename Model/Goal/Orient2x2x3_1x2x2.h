#ifndef _BUSYBIN_ORIENT2x2x3_1x2x2_H_
#define _BUSYBIN_ORIENT2x2x3_1x2x2_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Orient 2 layers and an adjacent 1x2x2.
   * The 2x2x3 is in the back, bottom, left.
   * The 1x2x2 is in the front, bottom, right.
   */
  class Orient2x2x3_1x2x2 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

