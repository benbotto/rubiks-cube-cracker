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
    corner_t urf =
    {
      cube.get(F::UP,    2, 2),
      cube.get(F::RIGHT, 0, 0),
      cube.get(F::FRONT, 0, 2)
    };

    // ULF 1 RBW.
    corner_t ulf =
    {
      cube.get(F::UP,    2, 0),
      cube.get(F::LEFT,  0, 2),
      cube.get(F::FRONT, 0, 0)
    };

    // DRF 2 OGW.
    corner_t drf =
    {
      cube.get(F::DOWN,  0, 2),
      cube.get(F::RIGHT, 2, 0),
      cube.get(F::FRONT, 2, 2)
    };

    // DLF 3 OBW.
    corner_t dlf =
    {
      cube.get(F::DOWN,  0, 0),
      cube.get(F::LEFT,  2, 2),
      cube.get(F::FRONT, 2, 0)
    };

    // URB 4 RGY.
    corner_t urb =
    {
      cube.get(F::UP,    0, 2),
      cube.get(F::RIGHT, 0, 2),
      cube.get(F::BACK,  0, 0)
    };

    // ULB 5 RBY.
    corner_t ulb =
    {
      cube.get(F::UP,    0, 0),
      cube.get(F::LEFT,  0, 0),
      cube.get(F::BACK,  0, 2)
    };

    // DRB 6 OGY.
    corner_t drb =
    {
      cube.get(F::DOWN,  2, 2),
      cube.get(F::RIGHT, 2, 2),
      cube.get(F::BACK,  2, 0)
    };

    // DLB 7 OBY.
    corner_t dlb =
    {
      cube.get(F::DOWN, 2, 0),
      cube.get(F::LEFT, 2, 0),
      cube.get(F::BACK, 2, 2)
    };

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
    array<unsigned, 6> factorials = {5040, 720, 120, 24, 6, 2};
    uint32_t index = 0;

    // Note that the last digit is always 0, and the second to last
    // remains unchanged (1!).
    for (unsigned i = 0; i < 6; ++i)
      index += lehmer[i] * factorials[i];
    index += lehmer[6];

    // Now get the orientation of the corners.  7 corner orientations dictate
    // the orientation of the 8th, so only 7 need to be stored.
    array<uchar, 7> cornerOrientations =
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
    array<unsigned, 6> b3Places = {729, 243, 81, 27, 9, 3};
    uint32_t orientationNum = 0;

    for (unsigned i = 0; i < 6; ++i)
      orientationNum += cornerOrientations[i] * b3Places[i];
    orientationNum += cornerOrientations[6];

    // Combine the permutation and orientation into a single index.
    // p * 3^7 + o;
    return index * 2187 + orientationNum;
  }

  /**
   * Given three face colors, return a unique index for a corner cubie.  The
   * index will be [0..7].
   * @param corner An array of three colors, in any order.
   */
  unsigned char CornerPatternDatabase::getCubieIndex(const corner_t& corner) const
  {
    // The colors range from 0 to 5, per RubiksCubeModel.h.
    // Shifting 1 left by 0...5 gives 1, 2, 4, 8, 16, 32.
    // Adding these together gives a unique number for each corner cubie.
    // RWG = 4  + 1 + 2  = 7,  index 0
    // RBW = 4  + 8 + 1  = 13, index 1
    // OGW = 16 + 2 + 1  = 19, index 2
    // OWB = 16 + 1 + 8  = 25, index 3
    // RGY = 4  + 2 + 32 = 38, index 4
    // RBY = 4  + 8 + 32 = 44, index 5
    // OGY = 16 + 2 + 32 = 50, index 6
    // OBY = 16 + 8 + 32 = 56, index 7
    uchar sideSum =
      (1 << (uchar)corner[0]) +
      (1 << (uchar)corner[1]) +
      (1 << (uchar)corner[2]);

    switch (sideSum)
    {
      case 7:
        return 0;
      case 13:
        return 1;
      case 19:
        return 2;
      case 25:
        return 3;
      case 38:
        return 4;
      case 44:
        return 5;
      case 50:
        return 6;
      default: // 56
        return 7;
    }
  }

  /**
   * Given three face colors, return the orientation of the corner cubie, 0, 1,
   * or 2.  The up or down facet must be the first in the corner array.  The
   * cube must have red on top, white in front.
   * Orientation 0: Red or orange is on the top or bottom.
   * Orientation 1: White or yellow is on the top or bottom.
   * Orientation 2: Blue or green is on the top or bottom.
   * @param corner An array of three colors, with the up or down facet first.
   */
  unsigned char CornerPatternDatabase::getCubieOrientation(const corner_t& corner) const
  {
    switch (corner[0])
    {
      case RubiksCubeModel::COLOR::RED:
      case RubiksCubeModel::COLOR::ORANGE:
        return 0;

      case RubiksCubeModel::COLOR::WHITE:
      case RubiksCubeModel::COLOR::YELLOW:
        return 1;

      default: // Blue or green.
        return 2;
    }
  }
}

