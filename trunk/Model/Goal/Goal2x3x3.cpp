#include "Goal2x3x3.h"

namespace busybin
{
  /**
   * Solve a 2x3x3 on the bottom.
   * @param cube The cube.
   */
  bool Goal2x3x3::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      this->LD && this->LDB && this->DB && this->RDB && this->RD && this->RDF && this->DF && this->LDF &&
      this->LB && this->RB && this->LF && this->RF;
  }

  /**
   * Describe the goal.
   */
  string Goal2x3x3::getDescription() const
  {
    return "Solve a 2x3x3 on the bottom.";
  }
}

