#include "GoalG1_G2.h"

namespace busybin
{
  /**
   * Orient all corners, and place UF, UB, DF, DB in the correct slice.
   * @param cube The cube.
   */
  bool GoalG1_G2::isSatisfied(RubiksCubeModel& cube)
  {
    // Corners, left and right facets.
    COLOR LUB = cube.get(FACE::LEFT, 0, 0);
    COLOR LUF = cube.get(FACE::LEFT, 0, 2);
    COLOR LDB = cube.get(FACE::LEFT, 2, 0);
    COLOR LDF = cube.get(FACE::LEFT, 2, 2);

    COLOR RUB = cube.get(FACE::RIGHT, 0, 2);
    COLOR RUF = cube.get(FACE::RIGHT, 0, 0);
    COLOR RDB = cube.get(FACE::RIGHT, 2, 2);
    COLOR RDF = cube.get(FACE::RIGHT, 2, 0);

    // Edges in the M slice (between R and L).
    COLOR UF = cube.get(FACE::UP,    2, 1);
    COLOR FU = cube.get(FACE::FRONT, 0, 1);

    COLOR UB = cube.get(FACE::UP,    0, 1);
    COLOR BU = cube.get(FACE::BACK,  0, 1);

    COLOR DF = cube.get(FACE::DOWN,  0, 1);
    COLOR FD = cube.get(FACE::FRONT, 2, 1);

    COLOR DB = cube.get(FACE::DOWN,  2, 1);
    COLOR BD = cube.get(FACE::BACK,  2, 1);


    return
      // All left/right corner facets either blue or green.
      (LUB == COLOR::BLUE || LUB == COLOR::GREEN) &&
      (LUF == COLOR::BLUE || LUF == COLOR::GREEN) &&
      (LDB == COLOR::BLUE || LDB == COLOR::GREEN) &&
      (LDF == COLOR::BLUE || LDF == COLOR::GREEN) &&
      (RUB == COLOR::BLUE || RUB == COLOR::GREEN) &&
      (RUF == COLOR::BLUE || RUF == COLOR::GREEN) &&
      (RDB == COLOR::BLUE || RDB == COLOR::GREEN) &&
      (RDF == COLOR::BLUE || RDF == COLOR::GREEN) &&

      // UF, UB, DF, DB in the M slice.  Note that the edges
      // are already oriented.
      (UF == COLOR::RED   || UF == COLOR::ORANGE)  &&
      (FU == COLOR::WHITE || FU == COLOR::YELLOW)  &&

      (UB == COLOR::RED   || UB == COLOR::ORANGE)  &&
      (BU == COLOR::WHITE || BU == COLOR::YELLOW)  &&

      (DF == COLOR::RED   || DF == COLOR::ORANGE)  &&
      (FD == COLOR::WHITE || FD == COLOR::YELLOW)  &&

      (DB == COLOR::RED   || DB == COLOR::ORANGE)  &&
      (BD == COLOR::WHITE || BD == COLOR::YELLOW);
  }

  /**
   * Describe the goal.
   */
  string GoalG1_G2::getDescription() const
  {
    return "Orient all corners, and place FU, FD, BU, BD in the correct slice.";
  }
}
