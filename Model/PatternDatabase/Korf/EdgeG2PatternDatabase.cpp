#include "EdgeG2PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG2PatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCubeIndexModel::EDGE EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // The permutation of 6 of the 12 edges.
    perm_t edgePerm =
    {
      iCube.getEdgeIndex(EDGE::BL),
      iCube.getEdgeIndex(EDGE::BR),
      iCube.getEdgeIndex(EDGE::DF),
      iCube.getEdgeIndex(EDGE::DL),
      iCube.getEdgeIndex(EDGE::DB),
      iCube.getEdgeIndex(EDGE::DR)
    };

    // And the orientation of each.
    array<uint8_t, 6> edgeOrientations =
    {
      iCube.getEdgeOrientation(EDGE::BL),
      iCube.getEdgeOrientation(EDGE::BR),
      iCube.getEdgeOrientation(EDGE::DF),
      iCube.getEdgeOrientation(EDGE::DL),
      iCube.getEdgeOrientation(EDGE::DB),
      iCube.getEdgeOrientation(EDGE::DR)
    };

    // Combined into a single 32-bit integer.
    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

