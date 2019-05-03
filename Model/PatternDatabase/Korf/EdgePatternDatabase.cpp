#include "EdgePatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage.  There are 12P6 * 2^6 possible scrambles.
   * (12 cubies occupying 6 positions in a group, and each cubie can be in 1 of
   * 2 states). Each scramble is reachable in 10 moves or fewer, so each move
   * can be stored in 4 bits.  That gives 12P6 * 2^6 / 2 / 1024 / 1024 (~20MB).
   */
  EdgePatternDatabase::EdgePatternDatabase() : PatternDatabase(42577920)
  {
  }

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

    // Treat the orientations as a base-2 number, and convert it
    // to base-10.
    array<unsigned, 5> b2Places = {32, 16, 8, 4, 2};
    uint32_t orientationNum = 0;

    for (unsigned i = 0; i < 5; ++i)
      orientationNum += edgeOrientations[i] * b2Places[i];
    orientationNum += edgeOrientations[5];

    // Combine the permutation and orientation into a single index.
    // p * 2^6 + o;
    return index * 64 + orientationNum;
  }
}

