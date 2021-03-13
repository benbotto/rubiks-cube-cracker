#ifndef _BUSYBIN_UNORDERED_PAIR_SET_INDEXER_H_
#define _BUSYBIN_UNORDERED_PAIR_SET_INDEXER_H_

#include <array>
using std::array;
#include <cstdint>
#include "../../Util/math.h"

namespace busybin
{
  template <size_t N>
  class UnorderedPairSetIndexer
  {
    typedef array<uint8_t, 2> pair_t;

    // This holds all unordered pairs of two numbers in the range [0..N) in
    // lexicographic order.  See generatePairs.  Storage required follows the
    // triangular number sequence: 1, 3, 6, 10, 15, ...
    // (1+2+3+4+5+...).  So if N is 8 (8 numbers), 7 pairs will start with 0, 6
    // will start with 1, 5 will start with 2, ..., giving 7+6+5+4+3+2+1=28
    // pairs.
    array<pair_t, N*(N-1)/2> pairs;

    // Variable base for each number, for example 6C2*4C2*2C2, 4C2*2C2, 2C2.
    array<uint32_t, (N-2)/2> bases;

    /**
     * Generate all unique pairs of numbers in the range [0...N), in
     * lexicographic order.  For example, if N is 8:
     * {0 1}, {0 2}, ..., {0 7}
     * {1 2}, {1 3}, ..., {1 7}
     *  ...
     * {6 7}
     */
    void generatePairs(unsigned pairInd, pair_t& pair, unsigned& pairsInd = 0)
    {
      if (pairInd == 2)
      {
        this->pairs[pairsInd++] = {pair[0], pair[1]};
        return;
      }

      unsigned start = pairInd == 0 ? 0 : pair[pairInd - 1] + 1;

      for (unsigned i = start; i < N; ++i)
      {
        pair[pairInd] = i;
        this->generatePairs(pairInd + 1, pair, pairsInd);
      }
    }

  public:
    /**
     * Precompute all possible pairs of numbers, [0...N), and the variable
     * number base for each rank digit.
     */
    UnorderedPairSetIndexer()
    {
      pair_t pair;
      unsigned pairsInd = 0;
      this->generatePairs(0, pair, pairsInd);

      // Pre-computed list of bases for each ranked pair.  The last base is 2C2,
      // the second to last base is 4C2*2C2, then 6C2*4C2*2C2, etc.
      this->bases[(N-2)/2 - 1] = 1; // 2C2.

      for (int i = (N-2)/2-2; i >= 0; --i)
        this->bases[i] = this->bases[i + 1] * choose((N-2) - 2*i, 2);
    }

    /**
     * Rank the set of pairs in lexicographic order.  @param set An array of
     * pairs.  Each pair of numbers must be in ascending order, and there must
     * not be any duplicate numbers amongs the pairs.  Examples when N is 8:
     *
     * {0,1}, {2,3}, {4,5}, {6,7} -> 0
     * {2,3}, {6,7}, {4,5}, {0,1} -> 1259
     * {2,4}, {0,1}, {3,5}, {6,7} -> 1260
     * {6,7}, {4,5}, {2,3}, {0,1} -> 2519
     *
     * This works by looping over each pair and finding its rank among pairs that
     * exclude numbers preceding it, then multiplying each rank by its variable
     * base.  So for {2,3}, {6,7}, {4,5}, {0,1}:
     *
     * {2,3} has rank 13.
     * {6,7} has rank 14 among pairs excluding 2 and 3.
     * {4,5} has rank 5 among pairs excluding 2, 3, 6, and 7.
     * {0,1} is ignored.
     *
     * 13*6C2*4C2*2C2 + 14*4C2*2C2 + 5*2C2 = 1259.
     */
    uint32_t rank(const array<pair_t, N/2>& set) const
    {
      uint32_t rank = 0;
      // Rank among this many pairs.  For N=8, 8C2->6C2->4C2->2C2 (28->15->6->1).
      unsigned numRemaining = N*(N-1)/2;
      array<pair_t, N*(N-1)/2> remaining = this->pairs;

      for (unsigned n = 0; n < (N-2)/2; ++n)
      {
        unsigned remainingInd = 0;
        const pair_t& sPair = set[n];

        for (unsigned r = 0; r < numRemaining; ++r)
        {
          const pair_t& rPair = remaining[r];

          if (sPair == rPair)
          {
            // Found the pair: rank it relative to the ramining pairs, and multiply
            // it by the base for digit n.
            rank += r * this->bases[n];
          }
          else if (
            sPair[0] != rPair[0] && sPair[0] != rPair[1] &&
            sPair[1] != rPair[0] && sPair[1] != rPair[1]
          )
          {
            // The pair excludes the numbers in set[n], so keep it in the
            // list of remaining pairs for the next digit's rank.
            remaining[remainingInd++] = rPair;
          }
        }

        // Number of remaining pairs.
        numRemaining = remainingInd;
      }

      return rank;
    }
  };
}

#endif
