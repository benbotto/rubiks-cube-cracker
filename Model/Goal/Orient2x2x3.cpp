#include "Orient2x2x3.h"

namespace busybin
{
  /**
   * Orient a 2x2x3 cube in the back, bottom.
   * @param cube The cube.
   */
  bool Orient2x2x3::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    // 2x2x3 in the bottom back.
    return this->LD && this->LDB && this->DB && this->RDB && this->RD && this->LB && this->RB;
  }

  /**
   * Describe the goal.
   */
  string Orient2x2x3::getDescription() const
  {
    return "Orient a 2x2x3 cube in the back, bottom.";
  }
}
