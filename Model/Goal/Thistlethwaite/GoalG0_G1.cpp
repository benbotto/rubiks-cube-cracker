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
    typedef RubiksCube::EDGE EDGE;

    const uint8_t disoriented = 1;
    const uint8_t numEdges    = 12;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // If any edge is disoriented, return false.
    for (uint8_t i = 0; i < numEdges; ++i)
    {
      if (iCube.getEdgeOrientation((EDGE)i) == disoriented)
        return false;
    }

    return true;
  }

  /**
   * Describe the goal.
   */
  string GoalG0_G1::getDescription() const
  {
    return "Orient all edges so that they can be moved home without quarter turns of U or D.";
  }
}
