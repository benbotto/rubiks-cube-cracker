#include "GoalG0_orient_edges.h"

namespace busybin
{
  /**
   * Orient all edges so that they can be moved home without quarter turns of U
   * or D.
   * @param cube The cube.
   */
  bool GoalG0_orient_edges::isSatisfied(RubiksCubeModel& cube)
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

    return
      (UF == COLOR::RED && FU == COLOR::WHITE) ||

    /*
    return
      // U(B|F), D(B|F), L(F|B), R(F|B) cannot be white or yellow.
      (UF != COLOR::WHITE && UF != COLOR::YELLOW) &&
      (UB != COLOR::WHITE && UB != COLOR::YELLOW) &&

      (DF != COLOR::WHITE && DF != COLOR::YELLOW) &&
      (DB != COLOR::WHITE && DB != COLOR::YELLOW) &&

      (LF != COLOR::WHITE && LF != COLOR::YELLOW) &&
      (LB != COLOR::WHITE && LB != COLOR::YELLOW) &&

      (RF != COLOR::WHITE && RF != COLOR::YELLOW) &&
      (RB != COLOR::WHITE && RB != COLOR::YELLOW) &&

      // U(L|R), D(L|R), F(L|R), B(L|R) cannot be blue or green.
      (UL != COLOR::BLUE && UL != COLOR::GREEN) &&
      (UR != COLOR::BLUE && UR != COLOR::GREEN) &&

      (DL != COLOR::BLUE && DL != COLOR::GREEN) &&
      (DR != COLOR::BLUE && DR != COLOR::GREEN) &&

      (FL != COLOR::BLUE && FL != COLOR::GREEN) &&
      (FR != COLOR::BLUE && FR != COLOR::GREEN) &&

      (BL != COLOR::BLUE && BL != COLOR::GREEN) &&
      (BR != COLOR::BLUE && BR != COLOR::GREEN) &&

      // L(U|D), R(U|D) cannot be yellow or white.
      (LU != COLOR::YELLOW || LU == COLOR::WHITE) && 
      (LD != COLOR::YELLOW || LD == COLOR::WHITE) && 

      (RU != COLOR::YELLOW || RU == COLOR::WHITE) && 
      (RD != COLOR::YELLOW || RD == COLOR::WHITE) && 

      // F(U|D), B(U|D) cannot be blue or green.
      (FU != COLOR::BLUE && FU != COLOR::GREEN) &&
      (FD != COLOR::BLUE && FD != COLOR::GREEN) &&

      (BU != COLOR::BLUE && BU != COLOR::GREEN) &&
      (BD != COLOR::BLUE && BD != COLOR::GREEN);*/

  }

  /**
   * Describe the goal.
   */
  string GoalG0_orient_edges::getDescription() const
  {
    return "Orient all edges so that they can be moved home without quarter turns of U or D.";
  }
}
