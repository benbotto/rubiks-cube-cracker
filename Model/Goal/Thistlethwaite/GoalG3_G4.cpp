#include "GoalG3_G4.h"

namespace busybin
{
  /**
   * Solve the cube using only half twists.  Half of the edge permutations are
   * reachable due to even parity.  1/6 of the corner permutations are
   * reachable due to even parity and fixed tetrad twists.
   *
   * @param cube The cube.
   */
  bool GoalG3_G4::isSatisfied(RubiksCube& cube)
  {
    typedef RubiksCube::CORNER CORNER;
    typedef RubiksCube::EDGE   EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);
    const uint8_t numEdges = 12;
    const uint8_t numCorners = 8;

    // All edges in their home position.  Only 10 need to be checked--the edges
    // have even parity at this point, so two edges can't be swapped.
    for (uint8_t i = 0; i < numEdges - 2; ++i)
    {
      if (iCube.getEdgeIndex((EDGE)i) != i)
        return false;
    }

    // All the corners are in their home positions.  Due to the even parity and
    // the fixed tetrad twists, only 5 need to be checked.  It's not possible
    // to have 3 oriented corners out of position.
    for (uint8_t i = 0; i < numCorners - 3; ++i)
    {
      if (iCube.getCornerIndex((CORNER)i) != i)
        return false;
    }

    return true;
  }

  /**
   * Describe the goal.
   */
  string GoalG3_G4::getDescription() const
  {
    return "Solve the cube using only half twists.";
  }
}
