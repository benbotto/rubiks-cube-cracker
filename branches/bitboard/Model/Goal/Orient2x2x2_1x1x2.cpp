#include "Orient2x2x2_1x1x2.h"

namespace busybin
{
  /**
   * Orient a 2x2x2 cube with an adjacent 1x1x2.
   * The 2x2x2 is in the back, bottom, left.
   * The 1x1x2 is in the front, left.
   * @param cube The cube.
   */
  bool Orient2x2x2_1x1x2::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    // The cube is oriented with a 2x2x2 in the front, bottom, left
    // courtesy of the last goal.  There are 6 ways of solving an
    // adjacent 1x1x2.
    return this->DB && this->LDB && this->LD && this->LB && this->LDF && (this->DF || this->LF);
  }

  /**
   * Describe the goal.
   */
  string Orient2x2x2_1x1x2::getDescription() const
  {
    string desc("Orient a 2x2x2 cube with an adjacent 1x1x2.\n");
    desc += "The 2x2x2 is in the back, bottom, left.\n";
    desc += "The 1x1x2 is in the front, left.";

    return desc;
  }
}
