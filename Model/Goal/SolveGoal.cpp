#include "SolveGoal.h"

namespace busybin
{
  /**
   * Solve the cube.
   * @param cube The cube.
   */
  bool SolveGoal::isSatisfied(RubiksCube& cube)
  {
    return cube.isSolved();
  }

  /**
   * Describe the goal.
   */
  string SolveGoal::getDescription() const
  {
    return "Solve the cube.";
  }
}
