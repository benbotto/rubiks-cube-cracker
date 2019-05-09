#include "CornerPatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage.  There are 8!*3^7 possible scrambles of
   * the edges.  Each scramble is reachable in 11 moves or fewer, so each move
   * can be stored in 4 bits.  That gives 8!*3^7 / 2 / 1024 / 1024 (~42MB).
   */
  CornerPatternDatabase::CornerPatternDatabase() : PatternDatabase(88179840)
  {
  }

  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t CornerPatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCubeIndexModel::CORNER CORNER;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // The permutation of the 8 corners.
    perm_t cornerPerm =
    {
      iCube.getCornerIndex(CORNER::ULB),
      iCube.getCornerIndex(CORNER::URB),
      iCube.getCornerIndex(CORNER::URF),
      iCube.getCornerIndex(CORNER::ULF),
      iCube.getCornerIndex(CORNER::DLF),
      iCube.getCornerIndex(CORNER::DLB),
      iCube.getCornerIndex(CORNER::DRB),
      iCube.getCornerIndex(CORNER::DRF)
    };

    // Get the Lehmer code, which is in a factoradic number system.
    perm_t lehmer;
    this->getLehmerCode(cornerPerm, lehmer);

    // Now convert the Lehmer code to a base-10 number.  To do so,
    // multiply each digit by it's corresponding factorial base.
    // E.g. the permutation 120 has a Lehmer code of 110, which is
    // 1 * 2! + 1 * 1! + 0 * 0! = 3.
    uint32_t index =
      lehmer[0] * 5040 +
      lehmer[1] * 720 +
      lehmer[2] * 120 +
      lehmer[3] * 24 +
      lehmer[4] * 6 +
      lehmer[5] * 2 +
      lehmer[6];

    // Now get the orientation of the corners.  7 corner orientations dictate
    // the orientation of the 8th, so only 7 need to be stored.
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

    // Treat the orientations as a base-3 number, and convert it
    // to base-10.
    uint32_t orientationNum =
      cornerOrientations[0] * 729 +
      cornerOrientations[1] * 243 +
      cornerOrientations[2] * 81 +
      cornerOrientations[3] * 27 +
      cornerOrientations[4] * 9 +
      cornerOrientations[5] * 3 +
      cornerOrientations[6];

    // Combine the permutation and orientation into a single index.
    // p * 3^7 + o;
    return index * 2187 + orientationNum;
  }
}

