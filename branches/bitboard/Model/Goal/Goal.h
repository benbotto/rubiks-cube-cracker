#ifndef _BUSYBIN_GOAL_H_
#define _BUSYBIN_GOAL_H_

#include "../RubiksCubeModel.h"
#include <string>
using std::string;

namespace busybin
{
  /**
   * Base class for cube solution goals.
   */
  class Goal
  {
  public:
    virtual bool isSatisfied(RubiksCubeModel& cube) = 0;
    virtual string getDescription() const = 0;
  };
}

#endif

