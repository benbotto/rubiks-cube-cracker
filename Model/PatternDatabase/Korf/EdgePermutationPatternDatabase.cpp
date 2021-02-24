#include "EdgePermutationPatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage.  There are 12 edges, giving 12! possible
   * permutations.  Each permutation can be reached in 10 moves or fewer, which
   * can be stored in a nibble, so this database uses 12! / 1024^2 / 2 = ~228MB.
   */
  EdgePermutationPatternDatabase::EdgePermutationPatternDatabase() : PatternDatabase(479001600)
  {
  }

  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgePermutationPatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCube::EDGE EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // The permutation of the 12 edges.
    perm_t edgePerm;

    for (unsigned i = 0; i < 12; ++i)
      edgePerm[i] = iCube.getEdgeIndex((EDGE)i);

    // Lehmer code->rank (see CornerPatternDatabase.cpp).
    return this->permIndexer.rank(edgePerm);
  }
}

