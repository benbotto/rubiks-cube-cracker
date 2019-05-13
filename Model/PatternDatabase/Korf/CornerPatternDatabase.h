#ifndef _BUSYBIN_CORNER_PATTERN_DATABASE_
#define _BUSYBIN_CORNER_PATTERN_DATABASE_

#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include "../PatternDatabase.h"
#include <cstdint>
#include <bitset>
using std::bitset;

namespace busybin
{
  /**
   * This class provides a map of all the possible scrambles of the 8 corner
   * cubies to the number of moves required to get the solved state.
   */
  class CornerPatternDatabase : public PatternDatabase
  {
    typedef array<uint8_t, 8> perm_t;
    typedef RubiksCube::FACE F;

    array<uint8_t, 256> onesCountLookup;

  public:
    CornerPatternDatabase();
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif
