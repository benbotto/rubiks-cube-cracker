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
    unsigned          edgeInd = 6;

    while (edgeInd != 12)
    {
      for (uint8_t i = 0; i < 12; ++i)
      {
        if (iCube.getEdgeIndex((EDGE)i) == edgeInd)
        {
          edgePerm[edgeInd - 6]         = i;
          edgeOrientations[edgeInd - 6] = iCube.getEdgeOrientation((EDGE)i);
          ++edgeInd;
          break;
        }
      }
    }

    // Combined into a single 32-bit integer.
    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

