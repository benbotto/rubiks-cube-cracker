#include "EdgePatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage.  There are 12P7 * 2^7 possible scrambles.
   * (7 cubies occupying 12 positions in a group, and each cubie can be in 1 of
   * 2 states). Each scramble is reachable in 11 moves or fewer, so each move
   * can be stored in 4 bits.  That gives 12P7 * 2^7 / 2 / 1024 / 1024 (~244MB).
   */
  EdgePatternDatabase::EdgePatternDatabase() : PatternDatabase(510935040)
  {
  }

  /**
   * Given an permutation of edge indexes and an array of edge orientations,
   * calculate a unique index into the pattern database.
   * @param edgePerm An array of 7 edges indexes, numbered 0-11 (6 edges could
   * occupy 12 places).
   * @param edgeOrientations An array of edge orientations, numbered 0-1 (each
   * edge can be in one of two orientations).
   */
  uint32_t EdgePatternDatabase::getDatabaseIndex(const perm_t& edgePerm,
    const array<uint8_t, 7>& edgeOrientations) const
  {
    // Rank the permutation using by creating a Lehmer code and converting it
    // to a base-10 number.
    //
    // This differs from the corner conversion, because there are the 7 edges
    // could occupy 12 positions.  E.g. there are 12 pick 7 (12P7) possible
    // permutations, which is 12!/(12-7)! = 3,991,680.  Each digit in the
    // Lehmer code is thus multipled by the number of partial permutations that
    // preceed it: l_0 * 11P6 + l_1 + 10P5 + l_2 * 9P4 + l_3 * 8P3 + l_4 * 7P2
    // + l_5 * 6P1 + l_6 * 7P0.  See CornerPatternDatabase.cpp for an
    // explanation.
    uint32_t rank = this->permIndexer.rank(edgePerm);

    // Treat the orientations as a base-2 number, and convert it
    // to base-10.
    uint32_t orientationNum =
      edgeOrientations[0] * 64 +
      edgeOrientations[1] * 32 +
      edgeOrientations[2] * 16 +
      edgeOrientations[3] * 8 +
      edgeOrientations[4] * 4 +
      edgeOrientations[5] * 2 +
      edgeOrientations[6];

    // Combine the permutation and orientation into a single index.
    // p * 2^7 + o;
    return rank * 128 + orientationNum;
  }
}

