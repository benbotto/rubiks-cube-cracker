#ifndef _BUSYBIN_G2_PATTERN_DATABASE_H_
#define _BUSYBIN_G2_PATTERN_DATABASE_H_

#include "../PatternDatabase.h"
#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include "../PatternDatabase.h"
#include "../PermutationIndexer.h"
#include <cstdint>
#include <array>
using std::array;

namespace busybin
{
  /**
   * A pattern database that holds the orientations of the 8 corners, and the
   * positions of 4 edges in the M slice (FU, FD, BU, BD).  Used for moving
   * from G1->G2 using the Thistlethwaite algorithm.
   */
  class G2PatternDatabase : public PatternDatabase
  {
    PermutationIndexer<12, 4> permIndexer;

  public:
    G2PatternDatabase();
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif
