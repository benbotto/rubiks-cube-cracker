#ifndef _BUSYBIN_CORNER_PATTERN_DATABASE_
#define _BUSYBIN_CORNER_PATTERN_DATABASE_

#include "../RubiksCubeModel.h"
#include "PatternDatabase.h"
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
    uchar getCubieIndex(const corner_t& corner) const;
    uchar getCubieOrientation(const corner_t& corner) const;
  };
}

#endif
