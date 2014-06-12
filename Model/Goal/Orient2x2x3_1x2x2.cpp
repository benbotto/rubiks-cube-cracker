#include "Orient2x2x3_1x2x2.h"

namespace busybin
{
  /**
   * Orient 2 layers and an adjacent 1x2x2.
   * The 2x2x3 is in the back, bottom, left.
   * The 1x2x2 is in the front, bottom, right.
   * @param cube The cube.
   */
  bool Orient2x2x3_1x2x2::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      // 2x2x3 solved and oriented in the bottom back.
      this->LD && this->LDB && this->DB && this->RDB && this->RD && this->LB && this->RB &&
      // 1x2x2 in the front right.
      this->DF && this->RDF && this->RF;
  }

  /**
   * Describe the goal.
   */
  string Orient2x2x3_1x2x2::getDescription() const
  {
    string desc("Orient 2 layers and an adjacent 1x2x2.\n");
    desc += "The 2x2x3 is in the back, bottom.\n";
    desc += "The 1x2x2 is in the front, bottom, right.";

    return desc;
  }
}
