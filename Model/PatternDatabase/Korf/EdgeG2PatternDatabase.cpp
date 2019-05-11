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

    // See EdgeG1PatternDatabase.cpp.  This is for the other 6 edges, those
    // with indexes greater than 5.
    array<uint8_t, 6> edgePerm;
    array<uint8_t, 6> edgeOrientations;
    unsigned          numIndexed = 0;

    for (uint8_t i = 0; i < 12 && numIndexed != 6; ++i)
    {
      uint8_t edgeInd = iCube.getEdgeIndex((EDGE)i);

      if (edgeInd > 5)
      {
        edgePerm[edgeInd - 6]         = i;
        edgeOrientations[edgeInd - 6] = iCube.getEdgeOrientation((EDGE)i);
        ++numIndexed;
      }
    }

    // Combined into a single 32-bit integer.
    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

