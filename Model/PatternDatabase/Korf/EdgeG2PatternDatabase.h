#ifndef _BUSYBIN_EDGE_G2_PATTERN_DATABASE_
#define _BUSYBIN_EDGE_G2_PATTERN_DATABASE_

#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include "EdgePatternDatabase.h"
#include <cstdint>

namespace busybin
{
  /**
   * See EdgeG1PatternDatabase.h.  This indexes the other 7 edges: FL, BL, BR, DF,
   * DL, DB, and DR.
   */
  class EdgeG2PatternDatabase : public EdgePatternDatabase
  {
  public:
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif
