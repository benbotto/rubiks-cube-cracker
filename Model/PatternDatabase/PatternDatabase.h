#ifndef _BUSYBIN_Pattern_PATTERN_DATABASE_
#define _BUSYBIN_Pattern_PATTERN_DATABASE_

#include "../RubiksCubeModel.h"
#include "../../Util/NibbleArray.h"
#include <cstdint>
#include <cstddef>
using std::size_t;

namespace busybin
{
  /**
   * Base class for the corner and edge pattern databases.  Provides
   * index-based lookups for the number of moves required to get a scrambled
   * cube to the solved state.
   */
  class PatternDatabase
  {
    NibbleArray database;

    PatternDatabase();

    size_t size;
    size_t numItems;

  protected:
    typedef unsigned char uchar;

  public:
    PatternDatabase(const size_t size);
    virtual uint32_t getDatabaseIndex(const RubiksCubeModel& cube) const = 0;
    bool setNumMoves(const RubiksCubeModel& cube, const uchar numMoves);
    bool setNumMoves(const uint32_t ind, const uchar numMoves);
    uchar getNumMoves(const RubiksCubeModel& cube) const;
    uchar getNumMoves(const uint32_t ind) const;
    size_t getSize() const;
    size_t getNumItems() const;
    bool isFull() const;

    /**
     * Given a permutation of cubies, return the Lehmer code.  This is used
     * for converting a permutation to a lexicographical index.
     * @param perm The permutation for which Lehmer will be calculated.
     * @param lehmer The Lehmer code for the index will be returned here.
     */
    template<size_t SIZE>
    void getLehmerCode(const array<uchar, SIZE>& perm,
      array<uchar, SIZE>& lehmer) const
    {
      // From Korf's paper:
      // https://www.cs.princeton.edu/courses/archive/fall06/cos402/papers/korfrubik.pdf
      //
      // To map a permutation to a sequence of factorial digits, we subtract from
      // each element the number of original elements to its left that are less
      // than it. For example, the mapping from permutations of three elements to
      // factorial base digits is: 012-000, 021-010, 102-100, 120-110, 201-200,
      // 210-210.  By reducing these factorial digits to an integer, we obtain
      // the desired values: 012-000-0, 021-010-1, 102-100-2, 120-110-3,
      // 201-200-4, 210-210-5.
      //
      // That given, the first factoradic number remains the same.
      lehmer = perm;

      for (unsigned i = 1; i < perm.size(); ++i)
      {
        unsigned j = i;

        while (j--)
        {
          if (perm[j] < perm[i])
            --lehmer[i];
        }
      }
    }
  };
}

#endif

