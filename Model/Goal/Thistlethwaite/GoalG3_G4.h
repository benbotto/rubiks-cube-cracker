#ifndef _BUSYBIN_GOALG3_G4_H_
#define _BUSYBIN_GOALG3_G4_H_

#include "../Goal.h"
#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include <cstdint>
#include <array>
using std::array;

namespace busybin
{
  /**
   * Solve the cube using only half twists.
   */
  class GoalG3_G4 : public Goal
  {
  public:
    bool isSatisfied(RubiksCube& cube);
    string getDescription() const;
  };
}

#endif
