#ifndef _BUSYBIN_CORNER_PERMUTATION_INDEXER_
#define _BUSYBIN_CORNER_PERMUTATION_INDEXER_

#include <array>
using std::array;
#include <cstdint>

namespace busybin
{
  /**
   * The Korf method for solving the Rubik's Cube utilizes three pattern
   * databases: one for the 8 corner pieces; one for 6 of the 12 edges; one for
   * the remaining 6.  This class is used to generate unique and sequential
   * indexes for each permutation of the 8 corners.  This is done by converting
   * each permutation to a Lehmer code, then using a factorial number system to
   * convert the permutation to a unique index.
   * https://www.aaai.org/Papers/AAAI/2005/AAAI05-219.pdf
   * Also see https://en.wikipedia.org/wiki/Factorial_number_system and
   * https://math.stackexchange.com/questions/1608168/random-solving-of-a-rubik-cube/1608689#1608689
   */
  class CornerPermutationIndexer
  {
    typedef unsigned char uchar;
    typedef array<uchar, 8> perm_t;

  public:
    uint32_t getPermutationIndex(const perm_t& perm) const;
  };
}

#endif

