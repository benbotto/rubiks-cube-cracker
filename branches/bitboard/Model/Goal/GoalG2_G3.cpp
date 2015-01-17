#include "GoalG2_G3.h"

namespace busybin
{
  /**
   * Get all edges in the correct slice and all corners in the correct orbit.
   * @param cube The cube.
   */
  bool GoalG2_G3::isSatisfied(RubiksCubeModel& cube)
  {
    // Corners.
    COLOR ULB = cube.get(FACE::UP,    0, 0);
    COLOR LUB = cube.get(FACE::LEFT,  0, 0);

    COLOR ULF = cube.get(FACE::UP,    2, 0);
    COLOR LUF = cube.get(FACE::LEFT,  0, 2);

    COLOR URB = cube.get(FACE::UP,    0, 2);
    COLOR RUB = cube.get(FACE::RIGHT, 0, 0);

    COLOR URF = cube.get(FACE::UP,    2, 2);
    COLOR RUF = cube.get(FACE::RIGHT, 0, 0);

    COLOR DLB = cube.get(FACE::DOWN,  2, 0);
    COLOR LDB = cube.get(FACE::LEFT,  2, 0);

    COLOR DLF = cube.get(FACE::DOWN,  0, 0);
    COLOR LDF = cube.get(FACE::LEFT,  2, 2);

    COLOR DRB = cube.get(FACE::DOWN,  2, 2);
    COLOR RDB = cube.get(FACE::RIGHT, 2, 2);

    COLOR DRF = cube.get(FACE::DOWN,  0, 2);
    COLOR RDF = cube.get(FACE::RIGHT, 2, 0);

    // Edges.  Note that the edge pieces in the M slice were taken care
    // of in the previous goal.
    COLOR UL = cube.get(FACE::UP,    1, 0);
    COLOR LU = cube.get(FACE::LEFT,  0, 1);

    COLOR UR = cube.get(FACE::UP,    1, 2);
    COLOR RU = cube.get(FACE::RIGHT, 0, 1);

    COLOR DL = cube.get(FACE::DOWN,  1, 0);
    COLOR LD = cube.get(FACE::LEFT,  2, 1);

    COLOR DR = cube.get(FACE::DOWN,  1, 2);
    COLOR RD = cube.get(FACE::RIGHT, 2, 1);

    COLOR LB = cube.get(FACE::LEFT,  1, 0);
    COLOR BL = cube.get(FACE::BACK,  1, 2);

    COLOR LF = cube.get(FACE::LEFT,  1, 2);
    COLOR FL = cube.get(FACE::FRONT, 1, 0);

    COLOR RB = cube.get(FACE::RIGHT, 1, 2);
    COLOR BR = cube.get(FACE::BACK,  1, 0);

    COLOR RF = cube.get(FACE::RIGHT, 1, 0);
    COLOR FR = cube.get(FACE::FRONT, 1, 2);


    // Ffter this goal, the cube will be solvable with only 180-degree turns.
    return
      // only 180-degree turns.
      (ULB == COLOR::RED || ULB == COLOR::ORANGE) && (LUB == COLOR::BLUE || LUB == COLOR::GREEN) && 
      (ULF == COLOR::RED || ULF == COLOR::ORANGE) && (LUF == COLOR::BLUE || LUF == COLOR::GREEN) &&
      (URB == COLOR::RED || URB == COLOR::ORANGE) && (RUB == COLOR::BLUE || RUB == COLOR::GREEN) && 
      (URF == COLOR::RED || URF == COLOR::ORANGE) && (RUF == COLOR::BLUE || RUF == COLOR::GREEN) &&
      (DLB == COLOR::RED || DLB == COLOR::ORANGE) && (LDB == COLOR::BLUE || LDB == COLOR::GREEN) && 
      (DLF == COLOR::RED || DLF == COLOR::ORANGE) && (LDF == COLOR::BLUE || LDF == COLOR::GREEN) &&
      (DRB == COLOR::RED || DRB == COLOR::ORANGE) && (RDB == COLOR::BLUE || RDB == COLOR::GREEN) && 
      (DRF == COLOR::RED || DRF == COLOR::ORANGE) && (RDF == COLOR::BLUE || RDF == COLOR::GREEN) &&

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
  string GoalG2_G3::getDescription() const
  {
    return "Get all edges in the correct slice and all corners in the correct orbit.";
  }
}
