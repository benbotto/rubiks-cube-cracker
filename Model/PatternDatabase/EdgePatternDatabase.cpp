#include "EdgePatternDatabase.h"
#include <iostream>
using std::cout;
using std::endl;

namespace busybin
{
  /**
   * Given an permutation of edge indexes and an array of edge orientations,
   * calculate a unique index into the pattern database.
   * @param edgePerm An array of 6 edges indexes, numbered 0-11 (12 edges could
   * occupy the 6 places).
   * @param edgeOrientations An array of edge orientations, numbered 0-1 (each
   * edge can be in one of two orientations).
   */
  uint32_t EdgePatternDatabase::getDatabaseIndex(const perm_t& edgePerm,
    const array<uchar, 6>& edgeOrientations) const
  {
    // Get the Lehmer code, which is in a factoradic number system.
    perm_t lehmer;
    this->getLehmerCode(edgePerm, lehmer);

    cout << "Edge lehmer code." << endl;
    for (uint32_t i : lehmer)
      cout << i << ' ';
    cout << endl;

    // Now convert the Lehmer code to a base-10 number.  This differs from the
    // corner conversion, because there are 12 edges that could occupy the 6
    // places in this group.  E.g. there are 12 pick 6 (12P6) possible permutations,
    // which is 12!/(12-6)! = 665,280.  Each digit in the Lehmer code is thus multipled
    // by the number of partial permutations that preceed it:
    // l_0 * 11P5 + l_1 + 10P4 + l_2 * 9P3 + l_3 * 8P2 + l_4 * 7P1 + l_5 * 6P0.
    array<unsigned, 5> factorials = {55440, 5040, 504, 56, 7};
    uint32_t index = 0;

    // Note that the last digit remains unchanged (6P0 == 1).
    for (unsigned i = 0; i < 5; ++i)
      index += lehmer[i] * factorials[i];
    index += lehmer[5];

    cout << "Lehmer in base 10: " << index << endl;

    // Treat the orientations as a base-2 number, and convert it
    // to base-10.
    array<unsigned, 5> b2Places = {32, 16, 8, 4, 2};
    uint32_t orientationNum = 0;

    for (unsigned i = 0; i < 5; ++i)
      orientationNum += edgeOrientations[i] * b2Places[i];
    orientationNum += edgeOrientations[5];

    cout << "Edge orientation in base 10: " << orientationNum << endl;

    // Combine the permutation and orientation into a single index.
    // p * 2^6 + o;
    return index * 64 + orientationNum;
  }

  /**
   * Given two face colors, return a unique index for an edge cubie.  The index
   * will be [0..11].
   * @param edge An array of two colors, in any order.
   */
  unsigned char EdgePatternDatabase::getCubieIndex(const edge_t& edge) const
  {
    // The colors range from 0 to 5, per RubiksCubeModel.h.
    // Shifting 1 left by 0...5 gives 1, 2, 4, 8, 16, 32.
    // Adding these together gives a unique number for each edge cubie.
    // RY = 4  + 32 = 36, index 0.
    // RG = 4  + 2  = 6,  index 1.
    // RW = 4  + 1  = 5,  index 2.
    // RB = 4  + 8  = 12, index 3.
    //
    // WG = 1  + 2  = 3,  index 4.
    // WB = 1  + 8  = 9,  index 5.
    // YB = 32 + 8  = 40, index 6.
    // YG = 32 + 2  = 34, index 7.
    //
    // OW = 16 + 1  = 17, index 8.
    // OB = 16 + 8  = 24, index 9.
    // OY = 16 + 32 = 48, index 10.
    // OG = 16 + 2  = 18, index 11.
    uchar sideSum =
      (1 << (uchar)edge[0]) +
      (1 << (uchar)edge[1]);

    switch (sideSum)
    {
      case 36:
        return 0;
      case 6:
        return 1;
      case 5:
        return 2;
      case 12:
        return 3;

      case 3:
        return 4;
      case 9:
        return 5;
      case 40:
        return 6;
      case 34:
        return 7;

      case 17:
        return 8;
      case 24:
        return 9;
      case 48:
        return 10;
      default: // 18
        return 11;
    }
  }

  /**
   * Given two face colors, return the orientation of the edge cubie, 0, or 1.
   * The up or down facet must be the first in the edge array for the top and
   * bottom layers, and the front or back facet must be the first edge in the
   * array for the middle layer..
   *
   * The cube is expected to be have red on top, white up front.
   *
   * Note that edges cannot be flipped (disoriented) without F or B turns, so
   * U, D, L, and R keep the edges oriented.
   *
   * Orientation 0: Bad (disoriented).
   * Orientation 1: Good.
   *
   * See: https://stackoverflow.com/questions/17305071/how-can-i-determine-optimally-if-an-edge-is-correctly-oriented-on-the-rubiks-cu
   * See: http://cube.crider.co.uk/zz.php?p=eoline#eo_detection
   *
   * @param edge An array of two colors.
   */
  unsigned char EdgePatternDatabase::getCubieOrientation(const edge_t& edge) const
  {
    // If the U or D sticker is the L or R color (blue or green), it's bad.
    if (edge[0] == RubiksCubeModel::COLOR::BLUE ||
      edge[0] == RubiksCubeModel::COLOR::GREEN)
    {
      return 0;
    }

    // If the U or D sticker is the F or B color (white or yellow), then check
    // the other edge.  If the other edge is the U or D color (red or orange),
    // it's bad.
    if (edge[0] == RubiksCubeModel::COLOR::WHITE ||
      edge[0] == RubiksCubeModel::COLOR::YELLOW)
    {
      if (edge[1] == RubiksCubeModel::COLOR::RED ||
        edge[1] == RubiksCubeModel::COLOR::ORANGE)
      {
        return 0;
      }
    }

    // Otherwise it's good.
    return 1;
  }
}

