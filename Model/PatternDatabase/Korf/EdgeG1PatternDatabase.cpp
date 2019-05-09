#include "EdgeG1PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG1PatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCubeIndexModel::EDGE EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // The permutation of 6 of the 12 edges.
    perm_t edgePerm =
    {
      iCube.getEdgeIndex(EDGE::UB),
      iCube.getEdgeIndex(EDGE::UR),
      iCube.getEdgeIndex(EDGE::UF),
      iCube.getEdgeIndex(EDGE::UL),
      iCube.getEdgeIndex(EDGE::FR),
      iCube.getEdgeIndex(EDGE::FL)
    };

    // And the orientation of each.
    array<uint8_t, 6> edgeOrientations =
    {
      iCube.getEdgeOrientation(EDGE::UB),
      iCube.getEdgeOrientation(EDGE::UR),
      iCube.getEdgeOrientation(EDGE::UF),
      iCube.getEdgeOrientation(EDGE::UL),
      iCube.getEdgeOrientation(EDGE::FR),
      iCube.getEdgeOrientation(EDGE::FL)
    };

    // Combined into a single 32-bit integer.
    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

