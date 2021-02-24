#include "EdgeG2PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG2PatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCube::EDGE EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // See EdgeG1PatternDatabase.cpp.  This is for the other 7 edges, those
    // with indexes greater than 4.
    array<uint8_t, 7> edgePerm;
    array<uint8_t, 7> edgeOrientations;
    unsigned          numIndexed = 0;

    for (uint8_t i = 0; i < 12 && numIndexed != 7; ++i)
    {
      uint8_t edgeInd = iCube.getEdgeIndex((EDGE)i);

      if (edgeInd > 4)
      {
        edgePerm[edgeInd - 5]         = i;
        edgeOrientations[edgeInd - 5] = iCube.getEdgeOrientation((EDGE)i);
        ++numIndexed;
      }
    }

    // Combined into a single 32-bit integer.
    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

