#include "GoalG0_G1.h"

namespace busybin
{
  /**
   * Orient all edges so that they can be moved home without quarter turns of U
   * or D.
   * @param cube The cube.
   */
  bool GoalG0_G1::isSatisfied(RubiksCube& cube)
  {
    COLOR UB = cube.getColor(FACE::UP, 0, 1);
    COLOR UL = cube.getColor(FACE::UP, 1, 0);
    COLOR UR = cube.getColor(FACE::UP, 1, 2);
    COLOR UF = cube.getColor(FACE::UP, 2, 1);

    COLOR LU = cube.getColor(FACE::LEFT, 0, 1);
    COLOR LB = cube.getColor(FACE::LEFT, 1, 0);
    COLOR LF = cube.getColor(FACE::LEFT, 1, 2);
    COLOR LD = cube.getColor(FACE::LEFT, 2, 1);

    COLOR FU = cube.getColor(FACE::FRONT, 0, 1);
    COLOR FL = cube.getColor(FACE::FRONT, 1, 0);
    COLOR FR = cube.getColor(FACE::FRONT, 1, 2);
    COLOR FD = cube.getColor(FACE::FRONT, 2, 1);

    COLOR RU = cube.getColor(FACE::RIGHT, 0, 1);
    COLOR RF = cube.getColor(FACE::RIGHT, 1, 0);
    COLOR RB = cube.getColor(FACE::RIGHT, 1, 2);
    COLOR RD = cube.getColor(FACE::RIGHT, 2, 1);

    COLOR BU = cube.getColor(FACE::BACK, 0, 1);
    COLOR BL = cube.getColor(FACE::BACK, 1, 0);
    COLOR BR = cube.getColor(FACE::BACK, 1, 2);
    COLOR BD = cube.getColor(FACE::BACK, 2, 1);

    COLOR DF = cube.getColor(FACE::DOWN, 0, 1);
    COLOR DL = cube.getColor(FACE::DOWN, 1, 0);
    COLOR DR = cube.getColor(FACE::DOWN, 1, 2);
    COLOR DB = cube.getColor(FACE::DOWN, 2, 1);

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
