#include "Orient2x2x2.h"

namespace busybin
{
  /**
   * Orient the 2x2x2 cube at the front, bottom, left.
   * @param cube The cube.
   */
  bool Orient2x2x2::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return this->LD && this->LDF && this->DF && this->LF;
  }

  /**
   * Describe the goal.
   */
  string Orient2x2x2::getDescription() const
  {
    return "Orient the 2x2x2 cube at the front, bottom, left.";
  }
}
