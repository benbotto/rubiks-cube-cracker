#ifndef _BUSYBIN_GOAL2x3x3_OE_H_
#define _BUSYBIN_GOAL2x3x3_OE_H_

#include "Goal.h"
#include "Goal2x3x3.h"
#include "../RubiksCubeModel.h"
#include <sstream>
using std::ostringstream;

namespace busybin
{
  /**
   * Solve a 2x3x3 and orient top edges.
   */
  class Goal2x3x3_OE : public Goal
  {
    unsigned  numToOrient;
    Goal2x3x3 goal2x3x3;

  public:
    Goal2x3x3_OE(unsigned numToOrient);

    bool isSatisfied(RubiksCubeModel& cube);
    string getDescription() const;
  };
}

#endif

