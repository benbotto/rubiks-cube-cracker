#include "SolveGoal.h"

namespace busybin
{
  /**
   * Solve the cube.
   * @param cube The cube.
   */
  bool SolveGoal::isSatisfied(RubiksCubeModel& cube)
  {
    return
      cube.getFace(FACE::FRONT) == 0x0000000000000000 &&
      cube.getFace(FACE::RIGHT) == 0x0101010101010101 &&
      cube.getFace(FACE::UP)    == 0x0202020202020202 &&
      cube.getFace(FACE::LEFT)  == 0x0303030303030303 &&
      cube.getFace(FACE::DOWN)  == 0x0404040404040404 &&
      cube.getFace(FACE::BACK)  == 0x0505050505050505;
  }

  /**
   * Describe the goal.
   */
  string SolveGoal::getDescription() const
  {
    return "Solve the cube.";
  }
}
