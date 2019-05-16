#include "OrientationPatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage.  There are 8 corners in three possible
   * orientations each, and 12 corners in 2 possible orientations each.  For
   * both corners and edges, the orientation of the last cubie is dictated by
   * the others, so there are 2^11 * 3^7 = 4,478,976 possible orientations
   * (4,478,976/2/1024^2 = 2.13MB of storage).
   */
  OrientationPatternDatabase::OrientationPatternDatabase() : PatternDatabase(4478976)
  {
  }

  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t OrientationPatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCubeIndexModel::CORNER CORNER;
    typedef RubiksCubeIndexModel::EDGE   EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // Convert the corner orientations to an int (treat the orientations as a
    // base-3 number).
    uint32_t cornerInd =
      iCube.getCornerOrientation(CORNER::ULB) * 729 +
      iCube.getCornerOrientation(CORNER::URB) * 243 +
      iCube.getCornerOrientation(CORNER::URF) * 81 +
      iCube.getCornerOrientation(CORNER::ULF) * 27 +
      iCube.getCornerOrientation(CORNER::DLF) * 9 +
      iCube.getCornerOrientation(CORNER::DLB) * 3 +
      iCube.getCornerOrientation(CORNER::DRB);

    // Likewise for the edges, but treat the orientations as base-2.
    uint32_t edgeInd =
      iCube.getEdgeOrientation(EDGE::UB) * 1024 +
      iCube.getEdgeOrientation(EDGE::UR) * 512 +
      iCube.getEdgeOrientation(EDGE::UF) * 256 +
      iCube.getEdgeOrientation(EDGE::UL) * 128 +
      iCube.getEdgeOrientation(EDGE::FR) * 64 +
      iCube.getEdgeOrientation(EDGE::FL) * 32 +
      iCube.getEdgeOrientation(EDGE::BL) * 16 +
      iCube.getEdgeOrientation(EDGE::BR) * 8 +
      iCube.getEdgeOrientation(EDGE::DF) * 4 +
      iCube.getEdgeOrientation(EDGE::DL) * 2 +
      iCube.getEdgeOrientation(EDGE::DB);

    // Combine the indexes into a single int: e * 3^7 + c;
    return edgeInd * 2187 + cornerInd;
  }
}

