#include "G2PatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage.
   *
   * For the four edges, there are 12C4 combinations: 4 edges and 12
   * positions, and the order does not matter.
   *
   * There are 8 corners, and the orientations of 7 dictate the orientation of
   * the 8th (because the total orientation of the corners is always divisible
   * by 3, so only 1/3 of the corner orientation permutations are reachable).
   * Corners have three possible orientations, so there are 3^7 corner
   * orientation permutations.
   *
   * 12C4 * 3^7 / 1024^2 / 2 = 1082565 / 1024 / 2 = ~528.60 KB on disk.
   */
  G2PatternDatabase::G2PatternDatabase() : PatternDatabase(1082565)
  {
  }

  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t G2PatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCube::EDGE   EDGE;
    typedef RubiksCube::CORNER CORNER;

    const uint8_t numEdges = 12;
    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // Find the position that each E-slice edge is occupying.  Ex: if the cubie
    // that's in the FL (4/WB) position when solved is in the FR (4) position,
    // edgeIndexes[0] == 4.  edgeCombo is in ascending order.
    array<uint8_t, 4> edgeCombo;

    unsigned comboInd = 0;
    for (uint8_t i = 0; i < numEdges && comboInd < 4; ++i)
    {
      uint8_t edgeInd = iCube.getEdgeIndex((EDGE)i);

      if (
        edgeInd == (uint8_t)EDGE::FR ||
        edgeInd == (uint8_t)EDGE::FL ||
        edgeInd == (uint8_t)EDGE::BL ||
        edgeInd == (uint8_t)EDGE::BR
      )
        edgeCombo[comboInd++] = i;
    }

    uint32_t rank = this->comboIndexer.rank(edgeCombo);

    // Now get the orientation of the corners.
    array<uint8_t, 7> cornerOrientations =
    {
      iCube.getCornerOrientation(CORNER::ULB),
      iCube.getCornerOrientation(CORNER::URB),
      iCube.getCornerOrientation(CORNER::URF),
      iCube.getCornerOrientation(CORNER::ULF),
      iCube.getCornerOrientation(CORNER::DLF),
      iCube.getCornerOrientation(CORNER::DLB),
      iCube.getCornerOrientation(CORNER::DRB)
    };

    // Treat the orientations as a base-3 number, and convert it to base-10.  7
    // corner orientations dictate the orientation of the 8th, so only 7 need
    // to be stored.
    uint32_t orientationNum =
      cornerOrientations[0] * 729 +
      cornerOrientations[1] * 243 +
      cornerOrientations[2] * 81 +
      cornerOrientations[3] * 27 +
      cornerOrientations[4] * 9 +
      cornerOrientations[5] * 3 +
      cornerOrientations[6];

    // Combine the two (3^7 == 2187).
    return rank * 2187 + orientationNum;
  }
}

