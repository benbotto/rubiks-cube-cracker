#include "GoalG1_G2.h"

namespace busybin
{
  /**
   * Orient all corners, and place FR, FL, BL, BR in the correct slice (E).  In
   * Thistlethwaite's implementation it's the M-slice edges that are positioned,
   * but in this implementation U and D leave the corner orientations intact,
   * and F and B flip edges.  (This cube is essentially rotated 90-degrees over
   * Z.)
   * @param cube The cube.
   */
  bool GoalG1_G2::isSatisfied(RubiksCube& cube)
  {
    typedef RubiksCube::CORNER CORNER;
    typedef RubiksCube::EDGE   EDGE;

    const uint8_t oriented   = 0;
    const uint8_t numCorners = 8;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // If any corner is disoriented, return false.
    for (uint8_t i = 0; i < numCorners; ++i)
    {
      if (iCube.getCornerOrientation((CORNER)i) != oriented)
        return false;
    }

    // The 4 edges E-slice edges.
    const array<EDGE, 4> edges = {EDGE::FR, EDGE::FL, EDGE::BL, EDGE::BR};

    for (unsigned i = 0; i < 4; ++i)
    {
      uint8_t edgeInd = iCube.getEdgeIndex(edges[i]);

      // If any edge in the E slice is not an E-slice edge, return false.
      // (E.g. if the RW edge is in the FL position.)
      if (
        edgeInd != (uint8_t)edges[0] &&
        edgeInd != (uint8_t)edges[1] &&
        edgeInd != (uint8_t)edges[2] &&
        edgeInd != (uint8_t)edges[3]
      )
        return false;
    }

    return true;
  }

  /**
   * Describe the goal.
   */
  string GoalG1_G2::getDescription() const
  {
    return "Orient all corners, and place FR, FL, BL, BR in the correct slice (E).";
  }
}

