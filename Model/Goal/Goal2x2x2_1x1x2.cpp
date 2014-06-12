#include "Goal2x2x2_1x1x2.h"

namespace busybin
{
  /**
   * Solve a 2x2x2 cube with an adjacent 1x1x2.
   * @param cube The cube.
   */
  bool Goal2x2x2_1x1x2::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    // The cube is oriented with a 2x2x2 in the front, bottom, left
    // courtesy of the last goal.  There are 6 ways of solving an
    // adjacent 1x1x2.
    return
      this->LD && this->LDF && this->DF && this->LF &&
      (
        (this->LDB && (this->DB || this->LB)) ||
        (this->LUF && (this->LU || this->UF)) ||
        (this->RDF && (this->RD || this->RF))
      );
  }

  /**
   * Describe the goal.
   */
  string Goal2x2x2_1x1x2::getDescription() const
  {
    return "Solve a 2x2x2 cube with an adjacent 1x1x2.";
  }
}
