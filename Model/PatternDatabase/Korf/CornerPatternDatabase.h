#ifndef _BUSYBIN_CORNER_PATTERN_DATABASE_
#define _BUSYBIN_CORNER_PATTERN_DATABASE_

#include "../../RubiksCubeModel.h"
#include "../PatternDatabase.h"
#include <cstdint>

namespace busybin
{
  /**
   * This class provides a map of all the possible scrambles of the 8 corner
   * cubies to the number of moves required to get the solved state.
   */
  class CornerPatternDatabase : public PatternDatabase
  {
    typedef array<RubiksCubeModel::COLOR, 3> corner_t;
    typedef array<uchar, 8> perm_t;
    typedef RubiksCubeModel::FACE F;

  public:
    CornerPatternDatabase();
    uint32_t getDatabaseIndex(const RubiksCubeModel& cube) const;

    /**
     * Given three face colors, return a unique index for a corner cubie.  The
     * index will be [0..7].
     * @param corner An array of three colors, in any order.
     */
    inline unsigned char getCubieIndex(const corner_t& corner) const
    {
      // The colors range from 0 to 5, per RubiksCubeModel.h.
      // Shifting 1 left by 0...5 gives 1, 2, 4, 8, 16, 32.
      // Adding these together gives a unique number for each corner cubie.
      // RWG = 4  + 1 + 2  = 7,  index 0
      // RBW = 4  + 8 + 1  = 13, index 1
      // OGW = 16 + 2 + 1  = 19, index 2
      // OWB = 16 + 1 + 8  = 25, index 3
      // RGY = 4  + 2 + 32 = 38, index 4
      // RBY = 4  + 8 + 32 = 44, index 5
      // OGY = 16 + 2 + 32 = 50, index 6
      // OBY = 16 + 8 + 32 = 56, index 7
      uchar sideSum =
        (1 << (uchar)corner[0]) +
        (1 << (uchar)corner[1]) +
        (1 << (uchar)corner[2]);

      switch (sideSum)
      {
        case 7:
          return 0;
        case 13:
          return 1;
        case 19:
          return 2;
        case 25:
          return 3;
        case 38:
          return 4;
        case 44:
          return 5;
        case 50:
          return 6;
        default: // 56
          return 7;
      }
    }

    /**
     * Given three face colors, return the orientation of the corner cubie, 0, 1,
     * or 2.  The up or down facet must be the first in the corner array.  The
     * cube must have red on top, white in front.
     * Orientation 0: Red or orange is on the top or bottom.
     * Orientation 1: White or yellow is on the top or bottom.
     * Orientation 2: Blue or green is on the top or bottom.
     * @param corner An array of three colors, with the up or down facet first.
     */
    inline unsigned char getCubieOrientation(const corner_t& corner) const
    {
      switch (corner[0])
      {
        case RubiksCubeModel::COLOR::RED:
        case RubiksCubeModel::COLOR::ORANGE:
          return 0;

        case RubiksCubeModel::COLOR::WHITE:
        case RubiksCubeModel::COLOR::YELLOW:
          return 1;

        default: // Blue or green.
          return 2;
      }
    }
  };
}

#endif
