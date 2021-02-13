#include "GoalG1_G2.h"

namespace busybin
{
  /**
   * Orient all corners, and place UF, UB, DF, DB in the correct slice (M).
   * @param cube The cube.
   */
  bool GoalG1_G2::isSatisfied(RubiksCube& cube)
  {
    typedef RubiksCubeIndexModel::CORNER CORNER;
    typedef RubiksCubeIndexModel::EDGE   EDGE;

    const uint8_t oriented   = 0;
    const uint8_t numCorners = 8;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // If any corner is disoriented, return false.
    for (uint8_t i = 0; i < numCorners; ++i)
    {
      if (iCube.getCornerOrientation((CORNER)i) != oriented)
        return false;
    }

    // The 4 edges M-slice edges.
    array<EDGE, 4> edges = {EDGE::UB, EDGE::UF, EDGE::DF, EDGE::DB};

    for (unsigned i = 0; i < 4; ++i)
    {
      uint8_t edgeInd = iCube.getEdgeIndex(edges[i]);

      // If any edge in the M slice is not an M-slice edge, return false.
      // (E.g. if the FL edge is in the UF position.)
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
    return "Orient all corners, and place FU, FD, BU, BD in the correct slice (M).";
  }
}

