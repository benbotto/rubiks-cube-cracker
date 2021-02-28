#ifndef _BUSYBIN_COMBINATION_INDEXER_H_
#define _BUSYBIN_COMBINATION_INDEXER_H_

#include "../../Util/math.h"
#include <array>
using std::array;
#include <cstdint>
#include <cstddef>

namespace busybin
{
  template<size_t N, size_t K>
  class CombinationIndexer
  {
    array<array<uint32_t, K+1>, N+1> choices;

  public:
    /**
     * Initialize a precomputed array of nCk (N and K inclusive).
     */
    CombinationIndexer()
    {
      for (unsigned n = 0; n <= N; ++n)
      {
        for (unsigned k = 0; k <= K; ++k)
          this->choices[n][k] = choose(n, k);
      }
    }

    /**
     * Get the rank of a combination.
     * @param comb A combination array in ascending order.
     */
    uint32_t rank(const array<uint8_t, K> comb) const
    {
      // https://www.dcode.fr/combination-rank
      // "With c_i elements in increasing order c_1, c_2, ..., c_k of a
      // combination of k elements among n the total number of elements, the
      // formula for calculating rank without listing all combinations is:
      // (nCk) - ((n-c_1)Ck) - ((n-c_2)C(k-1))-...-((n-c_k)C1)"
      //
      // That assumes 1-based combinations with ranks starting at 1, so each
      // element in the combination has 1 added to it, and the end result has 1
      // subtracted from it to make the rank 0-based.
      uint32_t rank = this->choices[N][K];

      for (unsigned i = 0; i < K; ++i)
        rank -= this->choices[N - (comb[i] + 1)][K - i];

      return rank - 1;
    }
  };
}

#endif
