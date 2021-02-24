#include "CornerPatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage.  There are 8!*3^7 possible scrambles of
   * the corners.  Each scramble is reachable in 11 moves or fewer, so each
   * move can be stored in 4 bits.  That gives 8!*3^7 / 2 / 1024 / 1024
   * (~42MB).
   */
  CornerPatternDatabase::CornerPatternDatabase() : PatternDatabase(88179840)
  {
  }

  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t CornerPatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCube::CORNER CORNER;

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

    // Compute the Lehmer code using Korf's linear algorithm.  It's discussed
    // in his paper, Large-Scale Parallel Breadth-First Search
    // (https://www.aaai.org/Papers/AAAI/2005/AAAI05-219.pdf).
    //
    // "We scan the permutation from left to right, constructing a bit string
    // of length n, indicating which elements of the permutation we've seen
    // so far. Initially the string is all zeros.  As each element of the
    // permutation is encountered, we use it as an index into the bit string
    // and set the corresponding bit to one. When we encounter element k in
    // the permutation, to determine the number of elements less than k to
    // its left, we need to know the number of ones in the first k bits of
    // our bit string. We extract the first k bits by right shifting the
    // string by n − k. This reduces the problem to: given a bit string,
    // count the number of one bits in it.
    // We solve this problem in constant time by using the bit string as an
    // index into a precomputed table, containing the number of ones in the
    // binary representation of each index."
    uint32_t rank = this->permIndexer.rank(cornerPerm);

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
    return rank * 2187 + orientationNum;
  }
}

