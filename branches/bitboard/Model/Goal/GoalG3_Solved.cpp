#include "GoalG3_Solved.h"

namespace busybin
{
  /**
   * Solve the cube.
   * @param cube The cube.
   */
  bool GoalG3_Solved::isSatisfied(RubiksCubeModel& cube)
  {
    // Corners.
    COLOR ULB = cube.get(FACE::UP,    0, 0);
    COLOR ULF = cube.get(FACE::UP,    2, 0);
    COLOR URB = cube.get(FACE::UP,    0, 2);
    COLOR URF = cube.get(FACE::UP,    2, 2);

    COLOR DLB = cube.get(FACE::DOWN,  2, 0);
    COLOR DLF = cube.get(FACE::DOWN,  0, 0);
    COLOR DRB = cube.get(FACE::DOWN,  2, 2);
    COLOR DRF = cube.get(FACE::DOWN,  0, 2);

    COLOR LUB = cube.get(FACE::LEFT,  0, 0);
    COLOR LUF = cube.get(FACE::LEFT,  0, 2);
    COLOR LDB = cube.get(FACE::LEFT,  2, 0);
    COLOR LDF = cube.get(FACE::LEFT,  2, 2);

    COLOR RUB = cube.get(FACE::RIGHT, 0, 0);
    COLOR RUF = cube.get(FACE::RIGHT, 0, 0);
    COLOR RDB = cube.get(FACE::RIGHT, 2, 2);
    COLOR RDF = cube.get(FACE::RIGHT, 2, 0);

    // Edges.  Note that the edge pieces in the M slice were taken care
    // of in the previous goal.
    COLOR UL = cube.get(FACE::UP,    1, 0);
    COLOR UR = cube.get(FACE::UP,    1, 2);
    COLOR UB = cube.get(FACE::UP,    0, 1);
    COLOR UF = cube.get(FACE::UP,    2, 1);

    COLOR DL = cube.get(FACE::DOWN,    1, 0);
    COLOR DR = cube.get(FACE::DOWN,    1, 2);
    COLOR DB = cube.get(FACE::DOWN,    2, 1);
    COLOR DF = cube.get(FACE::DOWN,    0, 1);

    COLOR LU = cube.get(FACE::LEFT,  0, 1);
    COLOR LD = cube.get(FACE::LEFT,  2, 1);
    COLOR LF = cube.get(FACE::LEFT,  1, 2);
    COLOR LB = cube.get(FACE::LEFT,  1, 0);

    COLOR RU = cube.get(FACE::RIGHT, 0, 1);
    COLOR RD = cube.get(FACE::RIGHT, 2, 1);
    COLOR RF = cube.get(FACE::RIGHT, 1, 0);
    COLOR RB = cube.get(FACE::RIGHT, 1, 2);

    COLOR FU = cube.get(FACE::FRONT, 0, 1);
    COLOR FD = cube.get(FACE::FRONT, 2, 1);
    COLOR FL = cube.get(FACE::FRONT, 1, 0);
    COLOR FR = cube.get(FACE::FRONT, 1, 2);

    COLOR BU = cube.get(FACE::BACK, 0, 1);
    COLOR BD = cube.get(FACE::BACK, 2, 1);
    COLOR BL = cube.get(FACE::BACK, 1, 2);
    COLOR BR = cube.get(FACE::BACK, 1, 0);

    return
      // Corners solved.
      ULB == COLOR::RED    && ULF == COLOR::RED    && URB == COLOR::RED    && URF == COLOR::RED    &&
      DLB == COLOR::ORANGE && DLF == COLOR::ORANGE && DRB == COLOR::ORANGE && DRF == COLOR::ORANGE &&
      LUB == COLOR::BLUE   && LDB == COLOR::BLUE   && LUF == COLOR::BLUE   && LDF == COLOR::BLUE   &&
      RUB == COLOR::GREEN  && RDB == COLOR::GREEN  && RUF == COLOR::GREEN  && RDF == COLOR::GREEN  &&

      // Edges solved.
      UL == COLOR::RED    && UR == COLOR::RED    && UF == COLOR::RED    && UB == COLOR::RED    &&
      DL == COLOR::ORANGE && DR == COLOR::ORANGE && DF == COLOR::ORANGE && DB == COLOR::ORANGE &&
      LU == COLOR::BLUE   && LD == COLOR::BLUE   && LF == COLOR::BLUE   && LB == COLOR::BLUE   &&
      RU == COLOR::GREEN  && RD == COLOR::GREEN  && RF == COLOR::GREEN  && RB == COLOR::GREEN  &&
      FU == COLOR::WHITE  && FD == COLOR::WHITE  && FL == COLOR::WHITE  && FR == COLOR::WHITE  &&
      BU == COLOR::YELLOW && BD == COLOR::YELLOW && BL == COLOR::YELLOW && BR == COLOR::YELLOW;
  }

  /**
   * Describe the goal.
   */
  string GoalG3_Solved::getDescription() const
  {
    return "Solve the cube.";
  }
}
