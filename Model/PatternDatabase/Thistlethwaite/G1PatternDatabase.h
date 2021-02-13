#ifndef _BUSYBIN_G1_PATTERN_DATABASE_H_
#define _BUSYBIN_G1_PATTERN_DATABASE_H_

#include "../PatternDatabase.h"
#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include "../PatternDatabase.h"
#include <cstdint>

namespace busybin
{
  /**
   * A pattern database that holds the orientations of the 12 edges.
   * Used for moving from G0->G1 using the Thistlethwaite algorithm.
   */
  class G1PatternDatabase : public PatternDatabase
  {
  public:
    G1PatternDatabase();
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif

