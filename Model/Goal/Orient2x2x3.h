#ifndef _BUSYBIN_ORIENT2x2x3_H_
#define _BUSYBIN_ORIENT2x2x3_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Orient a 2x2x3 cube in the back, bottom.
   */
  class Orient2x2x3 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

