#ifndef _BUSYBIN_EDGE_PATTERN_DATABASE_
#define _BUSYBIN_EDGE_PATTERN_DATABASE_

#include "../../RubiksCube.h"
#include "../PatternDatabase.h"
#include <cstdint>

namespace busybin
{
  /**
   * A base class for the two edge pattern databases.
   */
  class EdgePatternDatabase : public PatternDatabase
  {
  protected:
    typedef array<RubiksCube::COLOR, 2> edge_t;
    typedef array<uint8_t, 6> perm_t;
    typedef RubiksCube::FACE F;

    uint32_t getDatabaseIndex(const perm_t& edgePerm,
      const array<uint8_t, 6>& edgeOrientations) const;
  public:
    EdgePatternDatabase();
    virtual uint32_t getDatabaseIndex(const RubiksCube& cube) const = 0;

    /**
     * Given two face colors, return a unique index for an edge cubie.  The index
     * will be [0..11].
     * @param edge An array of two colors, in any order.
     */
    inline uint8_t getCubieIndex(const edge_t& edge) const
    {
      // The colors range from 0 to 5, per RubiksCube.h.
      // Shifting 1 left by 0...5 gives 1, 2, 4, 8, 16, 32.
      // Adding these together gives a unique number for each edge cubie.
      // RY = 4  + 32 = 36, index 0.
      // RG = 4  + 2  = 6,  index 1.
      // RW = 4  + 1  = 5,  index 2.
      // RB = 4  + 8  = 12, index 3.
      //
      // WG = 1  + 2  = 3,  index 4.
      // WB = 1  + 8  = 9,  index 5.
      // YB = 32 + 8  = 40, index 6.
      // YG = 32 + 2  = 34, index 7.
      //
      // OW = 16 + 1  = 17, index 8.
      // OB = 16 + 8  = 24, index 9.
      // OY = 16 + 32 = 48, index 10.
      // OG = 16 + 2  = 18, index 11.
      uint8_t sideSum =
        (1 << (uint8_t)edge[0]) +
        (1 << (uint8_t)edge[1]);

      switch (sideSum)
      {
        case 36:
          return 0;
        case 6:
          return 1;
        case 5:
          return 2;
        case 12:
          return 3;

        case 3:
          return 4;
        case 9:
          return 5;
        case 40:
          return 6;
        case 34:
          return 7;

        case 17:
          return 8;
        case 24:
          return 9;
        case 48:
          return 10;
        default: // 18
          return 11;
      }
    }

    /**
     * Given two face colors, return the orientation of the edge cubie, 0, or 1.
     * The up or down facet must be the first in the edge array for the top and
     * bottom layers, and the front or back facet must be the first edge in the
     * array for the middle layer..
     *
     * The cube is expected to be have red on top, white up front.
     *
     * Note that edges cannot be flipped (disoriented) without F or B turns, so
     * U, D, L, and R keep the edges oriented.
     *
     * Orientation 0: Bad (disoriented).
     * Orientation 1: Good.
     *
     * See: https://stackoverflow.com/questions/17305071/how-can-i-determine-optimally-if-an-edge-is-correctly-oriented-on-the-rubiks-cu
     * See: http://cube.crider.co.uk/zz.php?p=eoline#eo_detection
     *
     * @param edge An array of two colors.
     */
    inline uint8_t getCubieOrientation(const edge_t& edge) const
    {
      // If the U or D sticker is the L or R color (blue or green), it's bad.
      if (edge[0] == RubiksCube::COLOR::BLUE ||
        edge[0] == RubiksCube::COLOR::GREEN)
      {
        return 0;
      }

      // If the U or D sticker is the F or B color (white or yellow), then check
      // the other edge.  If the other edge is the U or D color (red or orange),
      // it's bad.
      if (edge[0] == RubiksCube::COLOR::WHITE ||
        edge[0] == RubiksCube::COLOR::YELLOW)
      {
        if (edge[1] == RubiksCube::COLOR::RED ||
          edge[1] == RubiksCube::COLOR::ORANGE)
        {
          return 0;
        }
      }

      // Otherwise it's good.
      return 1;
    }
  };
}

#endif
