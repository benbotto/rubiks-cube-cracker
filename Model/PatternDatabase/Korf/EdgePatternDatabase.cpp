#include "EdgePatternDatabase.h"

namespace busybin
{
  array<uint8_t, 4096> EdgePatternDatabase::onesCountLookup;

  /**
   * Initialize the database storage.  There are 12P7 * 2^7 possible scrambles.
   * (7 cubies occupying 12 positions in a group, and each cubie can be in 1 of
   * 2 states). Each scramble is reachable in 11 moves or fewer, so each move
   * can be stored in 4 bits.  That gives 12P7 * 2^7 / 2 / 1024 / 1024 (~244MB).
   */
  EdgePatternDatabase::EdgePatternDatabase() : PatternDatabase(510935040)
  {
    // See CornerPatternDatabase.cpp.  Lookup for fast Lehmer codes, but
    // for a permutation of size 12 (2^12).
    for (unsigned i = 0; i < 4096; ++i)
    {
      bitset<12> bits(i);
      this->onesCountLookup[i] = bits.count();
    }
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
    // See CornerPatternDatabase.cpp for an explanation.  Get the Lehmer code
    // using Korf's linear algorithm.
    perm_t lehmer;
    bitset<12> seen;

    lehmer[0] = edgePerm[0];
    seen[11 - edgePerm[0]] = 1;

    for (unsigned i = 0; i < 7; ++i)
    {
      seen[11 - edgePerm[i]] = 1;

      uint8_t numOnes = this->onesCountLookup[seen.to_ulong() >> (12 - edgePerm[i])];

      lehmer[i] = edgePerm[i] - numOnes;
    }

    // Now convert the Lehmer code to a base-10 number.  This differs from the
    // corner conversion, because there are the 7 edges could occupy 12
    // positions.  E.g. there are 12 pick 7 (12P7) possible permutations, which
    // is 12!/(12-7)! = 3,991,680.  Each digit in the Lehmer code is thus
    // multipled by the number of partial permutations that preceed it:
    // l_0 * 11P6 + l_1 + 10P5 + l_2 * 9P4 + l_3 * 8P3 + l_4 * 7P2 + l_5 * 6P1 + l_6 * 7P0.
    uint32_t index =
      lehmer[0] * 332640 +
      lehmer[1] * 30240 +
      lehmer[2] * 3024 +
      lehmer[3] * 336 +
      lehmer[4] * 42 +
      lehmer[5] * 6 +
      lehmer[6];

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
    return index * 128 + orientationNum;
  }
}

