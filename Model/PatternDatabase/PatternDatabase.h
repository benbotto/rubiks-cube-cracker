#ifndef _BUSYBIN_Pattern_PATTERN_DATABASE_
#define _BUSYBIN_Pattern_PATTERN_DATABASE_

#include "../RubiksCubeModel.h"
#include "../../Util/NibbleArray.h"
#include "../../Util/RubiksCubeException.h"
#include <cstdint>
#include <cstddef>
using std::size_t;
#include <fstream>
using std::ofstream;
using std::ifstream;
#include <string>
using std::string;
#include <vector>
using std::vector;

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

  public:
    PatternDatabase(const size_t size);
    virtual uint32_t getDatabaseIndex(const RubiksCubeModel& cube) const = 0;
    virtual bool setNumMoves(const RubiksCubeModel& cube, const uint8_t numMoves);
    virtual bool setNumMoves(const uint32_t ind, const uint8_t numMoves);
    virtual uint8_t getNumMoves(const RubiksCubeModel& cube) const;
    virtual uint8_t getNumMoves(const uint32_t ind) const;
    virtual size_t getSize() const;
    virtual size_t getNumItems() const;
    virtual bool isFull() const;
    virtual void toFile(const string& filePath) const;
    virtual bool fromFile(const string& filePath);
    virtual vector<uint8_t> inflate() const;

    /**
     * Given a permutation of cubies, return the Lehmer code.  This is used
     * for converting a permutation to a lexicographical index.
     * @param perm The permutation for which Lehmer will be calculated.
     * @param lehmer The Lehmer code for the index will be returned here.
     */
    template<size_t SIZE>
    void getLehmerCode(const array<uint8_t, SIZE>& perm,
      array<uint8_t, SIZE>& lehmer) const
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

