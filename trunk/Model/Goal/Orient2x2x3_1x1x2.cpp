#include "Orient2x2x3_1x1x2.h"

namespace busybin
{
  /**
   * Orient a 2x2x3 cube with an adjacent 1x1x2.
   * The 2x2x3 is in the back, and the 1x1x2 is in the front.
   * @param cube The cube.
   */
  bool Orient2x2x3_1x1x2::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      // 2x2x3 solved and oriented in the bottom back.
      this->LD && this->LDB && this->DB && this->RDB && this->RD && this->LB && this->RB &&
      (
        // 1x1x2 solved in the front left or front right.
        (this->LDF && (this->LF || this->DF)) ||
        (this->RDF && (this->RF || this->DF))
      );
  }

  /**
   * Describe the goal.
   */
  string Orient2x2x3_1x1x2::getDescription() const
  {
    string desc("Orient a 2x2x3 cube with an adjacent 1x1x2.\n");
    desc += "The 2x2x3 is in the back, bottom.\n";
    desc += "The 1x1x2 is in the front.";

    return desc;
  }
}
