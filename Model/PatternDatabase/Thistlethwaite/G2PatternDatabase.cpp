#include "G2PatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage.
   *
   * For the four edges, there are 12P4 permutations (4 edges and 12
   * positions).
   *
   * There are 8 corners, and the orientations of 7 dictate the orientation of
   * the 8th (because the total orientation of the corners is always divisible
   * by 3, so only 1/3 of the corner orientation permutations are reachable).
   * Corners have three possible orientations, so there are 3^7 corner
   * orientation permutations.
   *
   * 12P4 * 3^7 / 1024^2 / 2 = 25981560 / 1024^2 / 2 = ~12.39MB on disk.
   */
  G2PatternDatabase::G2PatternDatabase() : PatternDatabase(25981560)
  {
  }

  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t G2PatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCubeIndexModel::EDGE   EDGE;
    typedef RubiksCubeIndexModel::CORNER CORNER;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // Indexes of all edges.  The array indexes are the natural (solved-state) indexes,
    // so if the cubie that's in the UB (0/RY) position when solved is in the FR (4)
    // position, edgeIndexes[0] == 4.
    const uint8_t numEdges = 12;
    array<uint8_t, numEdges> edgeIndexes;

    for (uint8_t i = 0; i < numEdges; ++i)
      edgeIndexes[iCube.getEdgeIndex((EDGE)i)] = i;

    // Permutation of the 4 M-slice edges.
    array<uint8_t, 4> edgePerm =
    {
      edgeIndexes[(unsigned)EDGE::UB],
      edgeIndexes[(unsigned)EDGE::UF],
      edgeIndexes[(unsigned)EDGE::DF],
      edgeIndexes[(unsigned)EDGE::DB]
    };

    uint32_t rank = this->permIndexer.rank(edgePerm);

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

