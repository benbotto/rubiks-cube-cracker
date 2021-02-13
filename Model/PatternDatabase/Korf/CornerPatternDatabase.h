#ifndef _BUSYBIN_CORNER_PATTERN_DATABASE_
#define _BUSYBIN_CORNER_PATTERN_DATABASE_

#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include "../PatternDatabase.h"
#include "../PermutationIndexer.h"
#include <cstdint>

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

    PermutationIndexer<8> permIndexer;

  public:
    CornerPatternDatabase();
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif
