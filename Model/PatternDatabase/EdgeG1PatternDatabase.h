#ifndef _BUSYBIN_EDGE_G1_PATTERN_DATABASE_
#define _BUSYBIN_EDGE_G1_PATTERN_DATABASE_

#include "../RubiksCubeModel.h"
#include "EdgePatternDatabase.h"
#include <cstdint>

namespace busybin
{
  /**
   * A database for 6 of the 12 edge positions that indexes edge positions and
   * the number of moves required to get the edges to the solved state.  The 6
   * edges are the 4 in the top layer, and the front 2 of the middle layer.
   */
  class EdgeG1PatternDatabase : public EdgePatternDatabase
  {
  public:
    uint32_t getDatabaseIndex(const RubiksCubeModel& cube) const;
  };
}

#endif
