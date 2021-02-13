#ifndef _BUSYBIN_CORNER_PERMUTATION_INDEXER_
#define _BUSYBIN_CORNER_PERMUTATION_INDEXER_

#include "../../Util/math.h"
#include <cstdint>
#include <cstddef>
using std::size_t;
#include <array>
using std::array;
#include <bitset>
using std::bitset;
#include <iostream>
using std::cout;
using std::endl;

namespace busybin
{
  /**
   * Class for generating sequential indexes for permutations of size N picked K
   * ways.
   */
  template <size_t N, size_t K = N>
  class PermutationIndexer
  {
    // Precomputed table containing the number of ones in the binary
    // representation of each number.  The largest N-bit number is
    // 2^N-1 = (1 << N) - 1.
    array<uint32_t, (1 << N) - 1> onesCountLookup;

    // Precomputed table of factorials (or "picks" if N != K).  They're in
    // reverse order.
    array<uint32_t, K> factorials;

  public:
    /**
     * Popluate factorials and ones-count tables.
     */
    PermutationIndexer()
    {
      for (uint32_t i = 0; i < (1 << N) - 1; ++i)
      {
        bitset<N> bits(i);
        this->onesCountLookup[i] = bits.count();
      }

      for (uint32_t i = 0; i < K; ++i)
        this->factorials[i] = pick(N - 1 - i, K - 1 - i); 
    }

    /**
     * Calculate the lexicographic rank (the index) of a permutation in O(n)
     * complexity.
     */
    uint32_t rank(const array<uint8_t, K>& perm) const
    {
      // This will hold the Lehmer code (in a factorial number system).
      array<uint32_t, K> lehmer;

      // Set of "seen" digits in the permutation.
      bitset<N> seen;

      // The first digit of the Lehmer code is always the first digit of
      // the permutation.
      lehmer[0] = perm[0];

      // Mark the digit as seen (bitset uses right-to-left indexing).
      seen[N - 1 - perm[0]] = 1;

      for (uint32_t i = 1; i < K; ++i)
      {
        seen[N - 1 - perm[i]] = 1;

        // The number of "seen" digits to the left of this digit is the
        // count of ones left of this digit.
        uint32_t numOnes = this->onesCountLookup[seen.to_ulong() >> (N - perm[i])];

        lehmer[i] = perm[i] - numOnes;
      }

      // Convert the Lehmer code to base-10.
      uint32_t index = 0;

      for (uint32_t i = 0; i < K; ++i)
        index += lehmer[i] * this->factorials[i];

      return index;
    }
  };
}

#endif
