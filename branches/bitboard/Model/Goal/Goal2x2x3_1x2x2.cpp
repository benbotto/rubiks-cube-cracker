#include "Goal2x2x3_1x2x2.h"

namespace busybin
{
  /**
   * Solve 2 layers and an adjacent 1x2x2.
   * @param cube The cube.
   */
  bool Goal2x2x3_1x2x2::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      // 2x2x3 solved and oriented in the bottom back.
      this->LD && this->LDB && this->DB && this->RDB && this->RD && this->LB && this->RB &&
      (
        // 1x2x2 solved in the down front left or down front right.
        (this->DF && ((this->LDF && this->LF) || (this->RDF && this->RF))) ||

        // 1x2x2 solved in the top back left or top back right (rare).
        (this->UB && ((this->LUB && this->LU) || (this->RUB && this->RU)))
      );
  }

  /**
   * Describe the goal.
   */
  string Goal2x2x3_1x2x2::getDescription() const
  {
    return "Solve 2 layers and an adjacent 1x2x2.";
  }
}
