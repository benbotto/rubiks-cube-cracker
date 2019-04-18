#ifndef _BUSYBIN_EDGE_PERMUTATION_INDEXER_
#define _BUSYBIN_EDGE_PERMUTATION_INDEXER_

#include <array>
using std::array;
#include <cstdint>
#include <cmath>
using std::pow;

namespace busybin
{
  /**
   * The Korf method for solving the Rubik's Cube utilizes three pattern
   * databases: one for the 8 corner pieces; one for 6 of the 12 edges; one for
   * the remaining 6.  This class is used to generate unique and sequential
   * indexes for each permutation of 6 edges.  The order is lexicographical,
   * so (0 1 2 3 4 5), (0 1 2 3 4 6), (0 1 2 3 4 7), ..., (11 10 9 8 7 6)
   */
  class EdgePermutationIndexer
  {
    typedef unsigned char uchar;
    typedef array<uchar, 6> perm_t;

    // 2961307 is the permutation (11 10 9 8 7 6) converted to base 12 + 1.
    // I.e. The the sum from 6 to 11 of i*12^(i-6).
    // 6*12^0 + 7*12^1 + 8*12^2 + ... + 11*12^5
    // Thus, ~11.3MB of storage is used for this lookup table.
    array<uint32_t, 2961307> indexes;

    void genNextPerm(perm_t& perm, unsigned place, uint32_t& index);

  public:
    EdgePermutationIndexer();

    uint32_t permToBase10(const perm_t& perm) const;
    uint32_t getPermutationIndex(const perm_t& perm) const;
  };
}

#endif
