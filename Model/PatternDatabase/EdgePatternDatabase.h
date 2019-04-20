#ifndef _BUSYBIN_EDGE_PATTERN_DATABASE_
#define _BUSYBIN_EDGE_PATTERN_DATABASE_

#include "../RubiksCubeModel.h"
#include "PatternDatabase.h"
#include <cstdint>

namespace busybin
{
  /**
   * A base class for the two edge pattern databases.
   */
  class EdgePatternDatabase : public PatternDatabase
  {
  protected:
    typedef array<RubiksCubeModel::COLOR, 2> edge_t;
    typedef array<uchar, 6> perm_t;
    typedef RubiksCubeModel::FACE F;

    uint32_t getDatabaseIndex(const perm_t& edgePerm,
      const array<uchar, 6>& edgeOrientations) const;
  public:
    EdgePatternDatabase();
    virtual uint32_t getDatabaseIndex(const RubiksCubeModel& cube) const = 0;
    uchar getCubieIndex(const edge_t& edge) const;
    uchar getCubieOrientation(const edge_t& edge) const;
  };
}

#endif
