#include "EdgePermutationIndexer.h"

namespace busybin
{
  /**
   * Initialize the array of permutations, each of which points to its
   * sequential index.  This is a costly operation (it takes ~11.3 MB).
   */
  EdgePermutationIndexer::EdgePermutationIndexer() : indexes{{0xFFFFFFFF}}
  {
    perm_t perm = {0};
    uint32_t index = 0;

    this->genNextPerm(perm, 0, index);
  }

  /**
   * Given a permutation, perm, generate the next sequential permutation and
   * index it.
   * @param perm The current permutation, which will be moved to the next
   * sequential permutation.
   * @param place The current place in perm (0-5).
   * @param index The current permutation index.
   */
  void EdgePermutationIndexer::genNextPerm(perm_t& perm,
    unsigned place, uint32_t& index)
  {
    const uchar base = 12;

    if (place == perm.size())
    {
      // Set the index for the current permutation, which is converted from
      // base 12 to base 10 for space efficiency.
      this->indexes.at(this->permToBase10(perm)) = index++;
      return;
    }

    // This iterates through all combinations of base (0-11) for
    // each index (place) in perm.
    for (unsigned i = 0; i < base; ++i)
    {
      unsigned j = place;
      bool unique = true;

      // All elements of the permutation must be unique to be a permutation, so
      // check all elements preceeding "place."
      while (j-- && unique)
      {
        if (perm[j] == perm[place])
          unique = false;
      }

      // Move to the next place if the digits thusfar are unique.
      if (unique)
        this->genNextPerm(perm, place + 1, index);

      // Keep incrementing the digit at "place" until "base" is hit, then reset
      // to 0.
      perm[place] += 1;
    }

    perm[place] = 0;
  }

  /**
   * Convert a permutation of cubies, numbered 0-11, from base 12 to to base
   * 10.
   * @param perm The permutation of cubies, numbered 0-11.
   */
  uint32_t EdgePermutationIndexer::permToBase10(const perm_t& perm) const
  {
    uint32_t permNum = 0;

    for (unsigned i = 0; i < perm.size(); ++i)
      permNum += perm[i] * pow(12, perm.size() - i - 1);

    return permNum;
  }

  /**
   * Given a permutation of 6 of the 12 edge cubies, numbered 0-11, get
   * the uniqe permutation index.
   * @param perm The permutation of the edge cubies, numbered 0-11.
   */
  uint32_t EdgePermutationIndexer::getPermutationIndex(const perm_t& perm) const
  {
    return this->indexes[this->permToBase10(perm)];
  }
}

