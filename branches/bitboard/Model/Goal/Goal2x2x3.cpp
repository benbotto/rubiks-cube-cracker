#include "Goal2x2x3.h"

namespace busybin
{
  /**
   * Solve a 2x2x3 cube.
   * @param cube The cube.
   */
  bool Goal2x2x3::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    // Finish the 2x2x3 in the bottom left.
    return this->LD && this->LDF && this->DF && this->LF && this->DB && this->LDB && this->LB;
  }

  /**
   * Describe the goal.
   */
  string Goal2x2x3::getDescription() const
  {
    return "Solve a 2x2x3 cube.";
  }
}
