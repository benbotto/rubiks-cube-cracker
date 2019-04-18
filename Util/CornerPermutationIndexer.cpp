#include "CornerPermutationIndexer.h"

namespace busybin
{
  /**
   * Given a permutation of the 8 corner cubies, calculate a unique index for
   * the permutation.
   * @param perm The permutation of the edge cubies, numbered 0-8.
   */
  uint32_t CornerPermutationIndexer::getPermutationIndex(const perm_t& perm) const
  {
    // From Korf's paper.
    //
    // To map a permutation to a sequence of factorial digits, we subtract from
    // each element the number of original elements to its left that are less
    // than it. For example, the mapping from permutations of three elements to
    // factorial base digits is: 012-000, 021-010, 102-100, 120-110, 201-200,
    // 210-210.  By reducing these factorial digits to an integer, we obtain
    // the desired values: 012-000-0, 021-010-1, 102-100-2, 120-110-3,
    // 201-200-4, 210-210-5.
    //
    // That given, the first factoradic number remains the same, and the last
    // is always 0.
    perm_t lehmer = perm;
    lehmer[perm.size() - 1] = 0;

    for (unsigned i = 1; i < perm.size() - 1; ++i)
    {
      unsigned j = i;

      while (j--)
      {
        if (perm[j] < perm[i])
          --lehmer[i];
      }
    }

    // Now convert the Lehmer code to a base-10 number.  To do so,
    // multiply each digit by it's corresponding factorial base.
    // E.g. the permutation 120 has a Lehmer code of 110, which is
    // 1 * 2! + 1 * 1! + 0 * 0! = 3.
    array<unsigned, 8> factorials = {1, 1, 2, 6, 24, 120, 720, 5040};
    uint32_t index = 0;

    for (unsigned i = 0; i < perm.size() - 1; ++i)
      index += lehmer[i] * factorials[perm.size() - 1 - i];

    return index;
  }
}

