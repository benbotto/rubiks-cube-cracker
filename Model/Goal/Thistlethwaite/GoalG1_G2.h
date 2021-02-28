#ifndef _BUSYBIN_GOALG1_G2_H_
#define _BUSYBIN_GOALG1_G2_H_

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
  class GoalG1_G2 : public Goal
  {
  public:
    bool isSatisfied(RubiksCube& cube);
    string getDescription() const;
  };
}

#endif

