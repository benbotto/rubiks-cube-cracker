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
    typedef array<uint8_t, 6> perm_t;
    typedef RubiksCube::FACE F;

    uint32_t getDatabaseIndex(const perm_t& edgePerm,
      const array<uint8_t, 6>& edgeOrientations) const;
  public:
    EdgePatternDatabase();
    virtual uint32_t getDatabaseIndex(const RubiksCube& cube) const = 0;
  };
}

#endif
