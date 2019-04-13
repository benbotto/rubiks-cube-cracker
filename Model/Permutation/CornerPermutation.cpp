#include "CornerPermutation.h"

namespace busybin
{
  /**
   * Initialize the permutation index from a cube.
   * @param cube The current RubiksCubeModel.
   */
  CornerPermutation::CornerPermutation(const RubiksCubeModel& cube)
  {
    typedef RubiksCubeModel::FACE F;

    // URF 0 RGW.
    unsigned char urf = this->getCornerIndex(
      cube.get(F::UP,    2, 2),
      cube.get(F::RIGHT, 0, 0),
      cube.get(F::FRONT, 0, 2));

    // ULF 1 RBW
    unsigned char ulf = this->getCornerIndex(
      cube.get(F::UP,    2, 0),
      cube.get(F::LEFT,  0, 2),
      cube.get(F::FRONT, 0, 0));

    // DRF 2 OGW
    unsigned char drf = this->getCornerIndex(
      cube.get(F::DOWN,  0, 2),
      cube.get(F::RIGHT, 2, 0),
      cube.get(F::FRONT, 2, 2));

    // DLF 3 OBW
    unsigned char dlf = this->getCornerIndex(
      cube.get(F::DOWN,  0, 0),
      cube.get(F::LEFT,  2, 2),
      cube.get(F::FRONT, 2, 0));

    // URB 4 RGY
    unsigned char urb = this->getCornerIndex(
      cube.get(F::UP,    0, 2),
      cube.get(F::RIGHT, 0, 2),
      cube.get(F::BACK,  0, 0));

    // ULB 5 RBY
    unsigned char ulb = this->getCornerIndex(
      cube.get(F::UP,    0, 0),
      cube.get(F::LEFT,  0, 0),
      cube.get(F::BACK,  0, 2));

    // DRB 6 OGY
    unsigned char drb = this->getCornerIndex(
      cube.get(F::DOWN,  2, 2),
      cube.get(F::RIGHT, 2, 2),
      cube.get(F::BACK,  2, 0));

    // DLB 7 OBY
    unsigned char dlb = this->getCornerIndex(
      cube.get(F::DOWN, 2, 0),
      cube.get(F::LEFT, 2, 0),
      cube.get(F::BACK, 2, 2));

    cout << (unsigned)urf << ' ' <<
            (unsigned)ulf << ' ' <<
            (unsigned)drf << ' ' <<
            (unsigned)dlf << ' ' <<
            (unsigned)urb << ' ' <<
            (unsigned)ulb << ' ' <<
            (unsigned)drb << ' ' <<
            (unsigned)dlb << ' ' << endl;
  }

  /**
   * Given three face colors, return a unique index for a corner cubie.  The
   * index will be [0..7].
   */
  unsigned char CornerPermutation::getCornerIndex(
    const RubiksCubeModel::COLOR facet0,
    const RubiksCubeModel::COLOR facet1,
    const RubiksCubeModel::COLOR facet2) const
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
    unsigned char sideSum =
      (1 << (unsigned char)facet0) + (1 << (unsigned char)facet1) + (1 << (unsigned char)facet2);

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
}

