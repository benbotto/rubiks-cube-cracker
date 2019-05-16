#ifndef _BUSYBIN_ORIENTATION_PATTERN_DATABASE_H_
#define _BUSYBIN_ORIENTATION_PATTERN_DATABASE_H_

#include "../PatternDatabase.h"
#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include "../PatternDatabase.h"
#include <cstdint>

namespace busybin
{
  /**
   * A pattern database that holds the orientations of all 20 cubes.
   */
  class OrientationPatternDatabase : public PatternDatabase
  {
  public:
    OrientationPatternDatabase();
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif

