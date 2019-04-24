#include "OrientGoal.h"

namespace busybin
{
  /**
   * Orient the scambled cube with red on the top and white on the front.
   * @param cube The cube.
   */
  bool OrientGoal::isSatisfied(RubiksCubeModel& cube)
  {
    return cube.get(FACE::UP,    1, 1) == COLOR::RED &&
           cube.get(FACE::FRONT, 1, 1) == COLOR::WHITE;
  }

  /**
   * Describe the goal.
   */
  string OrientGoal::getDescription() const
  {
    return "Orient the scambled cube with red on the top and white on the front.";
  }
}
