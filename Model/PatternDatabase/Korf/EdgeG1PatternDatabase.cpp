#include "EdgeG1PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG1PatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCube::EDGE EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // Create a permutation array consisting of 7 of the 12 edges by looping
    // over all edge piece until the first 7 are found.  The permutation is
    // made up of the edges' positions, 0-11.
    array<uint8_t, 7> edgePerm;
    array<uint8_t, 7> edgeOrientations;
    unsigned          numIndexed = 0;

    for (uint8_t i = 0; i < 12 && numIndexed != 7; ++i)
    {
      uint8_t edgeInd = iCube.getEdgeIndex((EDGE)i);

      if (edgeInd < 7)
      {
        edgePerm[edgeInd]         = i;
        edgeOrientations[edgeInd] = iCube.getEdgeOrientation((EDGE)i);
        ++numIndexed;
      }
    }

    // Combine the edge permutation and orientation array into a single int.
    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

