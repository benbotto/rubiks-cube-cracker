#ifndef _BUSYBIN_GOALG1_G2_H_
#define _BUSYBIN_GOALG1_G2_H_

#include "../Goal.h"
#include "../../RubiksCube.h"

namespace busybin
{
  /**
   * Orient all corners, and place FU, FD, BU, BD in the correct slice.
   */
  class GoalG1_G2 : public Goal
  {
  public:
    bool isSatisfied(RubiksCube& cube);
    string getDescription() const;
  };
}

#endif

