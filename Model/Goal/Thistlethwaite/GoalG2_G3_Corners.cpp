#include "GoalG2_G3_Corners.h"

namespace busybin
{
  /**
   * Store the permutations of the corners that are achievable with only
   * 180-degree turns.
   * @param perms All permutations of corners in the G3 group.
   */
  GoalG2_G3_Corners::GoalG2_G3_Corners(GoalG3_Permute_Corners& perms)
  {
    this->perms = perms;
  }

  /**
   * Get all corners in their correct orbit such that they can be solved with
   * only 180-degree turns.
   * @param cube The cube.
   */
  bool GoalG2_G3_Corners::isSatisfied(RubiksCubeModel& cube)
  {
    return
      // All corners in a permutation that is achievable from the solved
      // state in only 180-degree turns.
      this->perms.permutationExists(cube);
  }

  /**
   * Describe the goal.
   */
  string GoalG2_G3_Corners::getDescription() const
  {
    return "Get all corners in their correct orbit such that they can be solved with only 180-degree turns.";
  }
}

