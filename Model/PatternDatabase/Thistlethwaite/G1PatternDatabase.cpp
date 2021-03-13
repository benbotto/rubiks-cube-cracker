#include "G1PatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage.  There are 12 edges, two orientations for
   * each, and the orientations of 11 dictate the orientation of the 12th
   * (because every twist either flips 0 or 4 edges, the total edge orientation
   * is always divisible by 2, so only 1/2 of the edge permutation orientations
   * are reachable).  There are then 2^11 orientations, and the database needs
   * 2^11 / 1024^2 / 2 = 1KB on disk.
   */
  G1PatternDatabase::G1PatternDatabase() : PatternDatabase(2048)
  {
  }

  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t G1PatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCube::EDGE EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // Treat the orientations as a base-2 number, and convert it to base-10.
    // Because 11 edges dictate the orientation of the 12th, only 11 edges
    // matter in this calculation.
    return
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
  }
}

