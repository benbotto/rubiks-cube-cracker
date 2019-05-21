#ifndef _BUSYBIN_EDGE_G1_PATTERN_DATABASE_
#define _BUSYBIN_EDGE_G1_PATTERN_DATABASE_

#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include "EdgePatternDatabase.h"
#include <cstdint>

namespace busybin
{
  /**
   * A database for 7 of the 12 edges that indexes edge positions and
   * the number of moves required to get the edges to the solved state.  The 7
   * edges are UB, UR, UF, UL, FR, FL, and BL.
   */
  class EdgeG1PatternDatabase : public EdgePatternDatabase
  {
  public:
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif
