#include "Goal3x3x3.h"

namespace busybin
{
  /**
   * Solve a 3x3x3 cube.
   * @param cube The cube.
   */
  bool Goal3x3x3::isSatisfied(RubiksCubeModel& cube)
  {
    //return cube.isSolved();
    return false;
  }

  /**
   * Describe the goal.
   */
  string Goal3x3x3::getDescription() const
  {
    return "Solve a 3x3x3 cube.";
  }
}
