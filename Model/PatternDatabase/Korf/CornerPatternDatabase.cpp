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
  uint32_t CornerPatternDatabase::getDatabaseIndex(const RubiksCubeModel& cube) const
  {
    // URF 0 RGW.
    corner_t urf = {cube.get(4), cube.get(24), cube.get(18)};

    // ULF 1 RBW.
    corner_t ulf = {cube.get(6), cube.get(10), cube.get(16)};

    // DRF 2 OGW.
    corner_t drf = {cube.get(42), cube.get(30), cube.get(20)};

    // DLF 3 OBW.
    corner_t dlf = {cube.get(40), cube.get(12), cube.get(22)};

    // URB 4 RGY.
    corner_t urb = {cube.get(2), cube.get(26), cube.get(32)};

    // ULB 5 RBY.
    corner_t ulb = {cube.get(0), cube.get(8), cube.get(34)};

    // DRB 6 OGY.
    corner_t drb = {cube.get(44), cube.get(28), cube.get(38)};

    // DLB 7 OBY.
    corner_t dlb = {cube.get(46), cube.get(14), cube.get(36)};

    // The permutation of the 8 corners.
    perm_t cornerPerm =
    {
      this->getCubieIndex(urf),
      this->getCubieIndex(ulf),
      this->getCubieIndex(drf),
      this->getCubieIndex(dlf),
      this->getCubieIndex(urb),
      this->getCubieIndex(ulb),
      this->getCubieIndex(drb),
      this->getCubieIndex(dlb)
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
      this->getCubieOrientation(urf),
      this->getCubieOrientation(ulf),
      this->getCubieOrientation(drf),
      this->getCubieOrientation(dlf),
      this->getCubieOrientation(urb),
      this->getCubieOrientation(ulb),
      this->getCubieOrientation(drb)
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

