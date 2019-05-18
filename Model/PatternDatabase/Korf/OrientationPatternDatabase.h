#ifndef _BUSYBIN_ORIENTATION_PATTERN_DATABASE_H_
#define _BUSYBIN_ORIENTATION_PATTERN_DATABASE_H_

#include "../PatternDatabase.h"
#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include "../PatternDatabase.h"
#include <cstdint>
#include <bitset>
using std::bitset;
#include <array>
using std::array;

namespace busybin
{
  /**
   * A pattern database that holds the orientations of all 20 cubes.
   */
  class OrientationPatternDatabase : public PatternDatabase
  {
    typedef array<uint8_t, 12> perm_t;

    static array<uint8_t, 4096> onesCountLookup;

  public:
    OrientationPatternDatabase();
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif

