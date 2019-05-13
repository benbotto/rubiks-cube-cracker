#include "EdgePatternDatabase.h"

namespace busybin
{
  array<uint8_t, 4096> EdgePatternDatabase::onesCountLookup;

  /**
   * Initialize the database storage.  There are 12P6 * 2^6 possible scrambles.
   * (12 cubies occupying 6 positions in a group, and each cubie can be in 1 of
   * 2 states). Each scramble is reachable in 10 moves or fewer, so each move
   * can be stored in 4 bits.  That gives 12P6 * 2^6 / 2 / 1024 / 1024 (~20MB).
   */
  EdgePatternDatabase::EdgePatternDatabase() : PatternDatabase(42577920)
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
   * @param edgePerm An array of 6 edges indexes, numbered 0-11 (12 edges could
   * occupy the 6 places).
   * @param edgeOrientations An array of edge orientations, numbered 0-1 (each
   * edge can be in one of two orientations).
   */
  uint32_t EdgePatternDatabase::getDatabaseIndex(const perm_t& edgePerm,
    const array<uint8_t, 6>& edgeOrientations) const
  {
    // See CornerPatternDatabase.cpp for an explanation.  Get the Lehmer code
    // using Korf's linear algorithm.
    perm_t lehmer;
    bitset<12> seen;

    lehmer[0] = edgePerm[0];
    seen[11 - edgePerm[0]] = 1;

    for (unsigned i = 0; i < 6; ++i)
    {
      seen[11 - edgePerm[i]] = 1;

      uint8_t numOnes = this->onesCountLookup[seen.to_ulong() >> (12 - edgePerm[i])];

      lehmer[i] = edgePerm[i] - numOnes;
    }

    // Now convert the Lehmer code to a base-10 number.  This differs from the
    // corner conversion, because there are 12 edges that could occupy the 6
    // places in this group.  E.g. there are 12 pick 6 (12P6) possible permutations,
    // which is 12!/(12-6)! = 665,280.  Each digit in the Lehmer code is thus multipled
    // by the number of partial permutations that preceed it:
    // l_0 * 11P5 + l_1 + 10P4 + l_2 * 9P3 + l_3 * 8P2 + l_4 * 7P1 + l_5 * 6P0.
    uint32_t index =
      lehmer[0] * 55440 +
      lehmer[1] * 5040 +
      lehmer[2] * 504 +
      lehmer[3] * 56 +
      lehmer[4] * 7 +
      lehmer[5];

    // Treat the orientations as a base-2 number, and convert it
    // to base-10.
    uint32_t orientationNum =
      edgeOrientations[0] * 32 +
      edgeOrientations[1] * 16 +
      edgeOrientations[2] * 8 +
      edgeOrientations[3] * 4 +
      edgeOrientations[4] * 2 +
      edgeOrientations[5];

    // Combine the permutation and orientation into a single index.
    // p * 2^6 + o;
    return index * 64 + orientationNum;
  }
}

