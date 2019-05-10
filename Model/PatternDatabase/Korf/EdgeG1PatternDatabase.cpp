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

    // Create a permutation array consisting of 6 of the 12 edges by looping
    // over all edge piece until the first 6 are found.  The permutation is
    // made up of the edges' positions, 0-11.
    array<uint8_t, 6> edgePerm;
    array<uint8_t, 6> edgeOrientations;
    unsigned          edgeInd = 0;

    for (uint8_t i = 0; i < 12 && edgeInd != 6; ++i)
    {
      if (iCube.getEdgeIndex((EDGE)i) < 6)
      {
        edgePerm[edgeInd]         = i;
        edgeOrientations[edgeInd] = iCube.getEdgeOrientation((EDGE)i);
        ++edgeInd;
      }
    }

    // Combine the edge permutation and orientation array into a single int.
    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

