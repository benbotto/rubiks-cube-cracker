#ifndef _BUSYBIN_CORNER_PERMUTATION_H_
#define _BUSYBIN_CORNER_PERMUTATION_H_

#include "../RubiksCubeModel.h"
#include <iostream>
using std::cout;
using std::endl;

namespace busybin
{
  /**
   * This class stores the permutation and orientation of the 8 corner cubies
   * in a compact form, with a fast comparator operator.  There are 8!
   * permutations of the corner cubies, and each can be in 3 possible
   * orientations.  Given the orientation of 7 of the corners, the last is
   * fixed, giving 3^7 possible orientations.  Hence there are
   * 8! * 3^7 = 88,179,840 possible states that the corners can be in, which
   * is a lot to hold in memory.
   */
  class CornerPermutation
  {
  public:
    CornerPermutation(const RubiksCubeModel& cube);

    unsigned char getCornerIndex(
      const RubiksCubeModel::COLOR facet0,
      const RubiksCubeModel::COLOR facet1,
      const RubiksCubeModel::COLOR facet2) const;
  };
}

#endif
