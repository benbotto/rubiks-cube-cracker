#ifndef _BUSYBIN_EDGE_PERMUTATION_INDEXER_
#define _BUSYBIN_EDGE_PERMUTATION_INDEXER_

#include <array>
using std::array;
#include <vector>
using std::vector;
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

    // A vector is used rather than an array because an array of this size
    // exceeds the stack space on most systems, and a vector allocates memory
    // dynamically.
    vector<uint32_t> indexes;

    void genNextPerm(perm_t& perm, unsigned place, uint32_t& index);

  public:
    EdgePermutationIndexer();

    uint32_t permToBase10(const perm_t& perm) const;
    uint32_t getPermutationIndex(const perm_t& perm) const;
  };
}

#endif
