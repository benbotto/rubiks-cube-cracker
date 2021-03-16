#ifndef _BUSYBIN_G4_PATTERN_DATABASE_H_
#define _BUSYBIN_G4_PATTERN_DATABASE_H_

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
   * A pattern database that holds the permutation of the positions of the
   * edges in each slice and the corners in each tetrad.  Used for moving from
   * G3->G4 using the Thistlethwaite algorithm.
   */
  class G4PatternDatabase : public PatternDatabase
  {
    PermutationIndexer<4> permIndexer;
    PermutationIndexer<4, 2> partialPermIndexer;
  public:
    G4PatternDatabase();
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif
