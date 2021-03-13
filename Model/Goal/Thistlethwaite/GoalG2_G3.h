#ifndef _BUSYBIN_GOALG2_G3_H_
#define _BUSYBIN_GOALG2_G3_H_

#include "../Goal.h"
#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include <cstdint>
#include <array>
using std::array;

namespace busybin
{
  /**
   * Orient all corners, and place FL, FR, BL, BR in the correct slice (E).
   */
  class GoalG2_G3 : public Goal
  {
  public:
    bool isSatisfied(RubiksCube& cube);
    string getDescription() const;
  };
}

#endif

