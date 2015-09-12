#ifndef _BUSYBIN_ORIENTG0_H_
#define _BUSYBIN_ORIENTG0_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Orient the scambled cube with red on the top and white on the front.
   */
  class OrientG0 : public Goal
  {
  public:
    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

