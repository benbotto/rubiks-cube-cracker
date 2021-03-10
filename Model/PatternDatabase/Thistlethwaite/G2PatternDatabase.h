#ifndef _BUSYBIN_G2_PATTERN_DATABASE_H_
#define _BUSYBIN_G2_PATTERN_DATABASE_H_

#include "../PatternDatabase.h"
#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include "../PatternDatabase.h"
#include "../CombinationIndexer.h"
#include <cstdint>
#include <array>
using std::array;

namespace busybin
{
  /**
   * A pattern database that holds the orientations of the 8 corners, and the
   * positions of 4 edges in the E slice (FR, FL, BL, BR).  Used for moving
   * from G1->G2 using the Thistlethwaite algorithm.
   */
  class G2PatternDatabase : public PatternDatabase
  {
    CombinationIndexer<12, 4> comboIndexer;

  public:
    G2PatternDatabase();
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif

