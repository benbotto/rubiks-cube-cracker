#include "GoalG2_G3_Edges.h"

namespace busybin
{
  /**
   * Store the permutations of the corners that are achievable with only
   * 180-degree turns.
   * @param perms All permutations of corners in the G3 group.
   */
  GoalG2_G3_Edges::GoalG2_G3_Edges(GoalG3_Permute_Corners& perms)
  {
    this->perms = perms;
  }

  /**
   * Get all edges in the correct slice so that they can be solved with only
   * 180-degree turns.
   * @param cube The cube.
   */
  bool GoalG2_G3_Edges::isSatisfied(RubiksCube& cube)
  {
    // Edges.  Note that the edge pieces in the M slice were taken care
    // of in the G1->G2 goal.
    COLOR UL = cube.getColor(FACE::UP,    1, 0);
    COLOR LU = cube.getColor(FACE::LEFT,  0, 1);

    COLOR UR = cube.getColor(FACE::UP,    1, 2);
    COLOR RU = cube.getColor(FACE::RIGHT, 0, 1);

    COLOR DL = cube.getColor(FACE::DOWN,  1, 0);
    COLOR LD = cube.getColor(FACE::LEFT,  2, 1);

    COLOR DR = cube.getColor(FACE::DOWN,  1, 2);
    COLOR RD = cube.getColor(FACE::RIGHT, 2, 1);

    COLOR LB = cube.getColor(FACE::LEFT,  1, 0);
    COLOR BL = cube.getColor(FACE::BACK,  1, 2);

    COLOR LF = cube.getColor(FACE::LEFT,  1, 2);
    COLOR FL = cube.getColor(FACE::FRONT, 1, 0);

    COLOR RB = cube.getColor(FACE::RIGHT, 1, 2);
    COLOR BR = cube.getColor(FACE::BACK,  1, 0);

    COLOR RF = cube.getColor(FACE::RIGHT, 1, 0);
    COLOR FR = cube.getColor(FACE::FRONT, 1, 2);


    // After this goal, the cube will be solvable with only 180-degree turns.
    return
      // All corners in a permutation that is achievable from the solved
      // state in only 180-degree turns.
      this->perms.permutationExists(cube) &&
        
      // Edges in their slices.
      (UL == COLOR::RED   || UL == COLOR::ORANGE) && (LU == COLOR::BLUE || LU == COLOR::GREEN)  &&
      (UR == COLOR::RED   || UR == COLOR::ORANGE) && (RU == COLOR::BLUE || RU == COLOR::GREEN)  &&
      (DL == COLOR::RED   || DL == COLOR::ORANGE) && (LD == COLOR::BLUE || LD == COLOR::GREEN)  &&
      (DR == COLOR::RED   || DR == COLOR::ORANGE) && (RD == COLOR::BLUE || RD == COLOR::GREEN)  &&
      (BL == COLOR::WHITE || BL == COLOR::YELLOW) && (LB == COLOR::BLUE || LB == COLOR::GREEN)  &&
      (FL == COLOR::WHITE || FL == COLOR::YELLOW) && (LF == COLOR::BLUE || LF == COLOR::GREEN)  &&
      (BR == COLOR::WHITE || BR == COLOR::YELLOW) && (RB == COLOR::BLUE || RB == COLOR::GREEN)  &&
      (FR == COLOR::WHITE || FR == COLOR::YELLOW) && (RF == COLOR::BLUE || RF == COLOR::GREEN);
  }

  /**
   * Describe the goal.
   */
  string GoalG2_G3_Edges::getDescription() const
  {
    return "Get all edges in the correct slice so that they can be solved with only 180-degree turns.";
  }
}

