#include "Goal2x2x3_1x1x2.h"

namespace busybin
{
  /**
   * Solve a 2x2x3 cube with an adjacent 1x1x2.
   * @param cube The cube.
   */
  bool Goal2x2x3_1x1x2::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      // 2x2x3 solved and oriented in the bottom back.
      this->LD && this->LDB && this->DB && this->RDB && this->RD && this->LB && this->RB &&
      (
        // 1x1x2 solved in the front right or front left.
        (this->LDF && (this->LF || this->DF)) ||
        (this->RDF && (this->RF || this->DF)) ||

        // 1x1x2 solved in the top right or top left.
        (this->LUB && (this->LU || this->UB)) ||
        (this->RUB && (this->RU || this->UB))
      );
  }

  /**
   * Describe the goal.
   */
  string Goal2x2x3_1x1x2::getDescription() const
  {
    return "Solve a 2x2x3 cube with an adjacent 1x1x2.";
  }
}
