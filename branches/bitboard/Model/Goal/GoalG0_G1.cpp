#include "GoalG0_G1.h"

namespace busybin
{
  /**
   * Orient all edges so that they can be moved home without quarter turns of U
   * or D.
   * @param cube The cube.
   */
  bool GoalG0_G1::isSatisfied(RubiksCubeModel& cube)
  {
    COLOR UB = cube.get(FACE::UP, 0, 1);
    COLOR UL = cube.get(FACE::UP, 1, 0);
    COLOR UR = cube.get(FACE::UP, 1, 2);
    COLOR UF = cube.get(FACE::UP, 2, 1);

    COLOR LU = cube.get(FACE::LEFT, 0, 1);
    COLOR LB = cube.get(FACE::LEFT, 1, 0);
    COLOR LF = cube.get(FACE::LEFT, 1, 2);
    COLOR LD = cube.get(FACE::LEFT, 2, 1);

    COLOR FU = cube.get(FACE::FRONT, 0, 1);
    COLOR FL = cube.get(FACE::FRONT, 1, 0);
    COLOR FR = cube.get(FACE::FRONT, 1, 2);
    COLOR FD = cube.get(FACE::FRONT, 2, 1);

    COLOR RU = cube.get(FACE::RIGHT, 0, 1);
    COLOR RF = cube.get(FACE::RIGHT, 1, 0);
    COLOR RB = cube.get(FACE::RIGHT, 1, 2);
    COLOR RD = cube.get(FACE::RIGHT, 2, 1);

    COLOR BU = cube.get(FACE::BACK, 0, 1);
    COLOR BL = cube.get(FACE::BACK, 1, 0);
    COLOR BR = cube.get(FACE::BACK, 1, 2);
    COLOR BD = cube.get(FACE::BACK, 2, 1);

    COLOR DF = cube.get(FACE::DOWN, 0, 1);
    COLOR DL = cube.get(FACE::DOWN, 1, 0);
    COLOR DR = cube.get(FACE::DOWN, 1, 2);
    COLOR DB = cube.get(FACE::DOWN, 2, 1);

    // See the spreadsheet in this directory for possible "good" edges.  Each
    // should be movable to its solved position without using U, U', D, or D'.
    return
      (UF == COLOR::BLUE  || UF == COLOR::GREEN || FU == COLOR::WHITE || FU == COLOR::YELLOW) &&
      (UB == COLOR::BLUE  || UB == COLOR::GREEN || BU == COLOR::WHITE || BU == COLOR::YELLOW) &&
      (DF == COLOR::BLUE  || DF == COLOR::GREEN || FD == COLOR::WHITE || FD == COLOR::YELLOW) &&
      (DB == COLOR::BLUE  || DB == COLOR::GREEN || BD == COLOR::WHITE || BD == COLOR::YELLOW) &&
      (LU == COLOR::BLUE  || LU == COLOR::GREEN || UL == COLOR::WHITE || UL == COLOR::YELLOW) &&
      (LD == COLOR::BLUE  || LD == COLOR::GREEN || DL == COLOR::WHITE || DL == COLOR::YELLOW) &&
      (RU == COLOR::BLUE  || RU == COLOR::GREEN || UR == COLOR::WHITE || UR == COLOR::YELLOW) &&
      (RD == COLOR::BLUE  || RD == COLOR::GREEN || DR == COLOR::WHITE || DR == COLOR::YELLOW) &&
      (LF == COLOR::BLUE  || LF == COLOR::GREEN || FL == COLOR::WHITE || FL == COLOR::YELLOW) &&
      (LB == COLOR::BLUE  || LB == COLOR::GREEN || BL == COLOR::WHITE || BL == COLOR::YELLOW) &&
      (RF == COLOR::BLUE  || RF == COLOR::GREEN || FR == COLOR::WHITE || FR == COLOR::YELLOW) &&
      (RB == COLOR::BLUE  || RB == COLOR::GREEN || BR == COLOR::WHITE || BR == COLOR::YELLOW);
  }

  /**
   * Describe the goal.
   */
  string GoalG0_G1::getDescription() const
  {
    return "Orient all edges so that they can be moved home without quarter turns of U or D.";
  }
}
