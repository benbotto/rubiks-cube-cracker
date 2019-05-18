#include "OrientationPatternDatabase.h"

namespace busybin
{
  array<uint8_t, 4096> OrientationPatternDatabase::onesCountLookup;

  /**
   * Initialize the database storage.  There are 8 corners in three possible
   * orientations each, and 12 corners in 2 possible orientations each.  For
   * both corners and edges, the orientation of the last cubie is dictated by
   * the others, so there are 2^11 * 3^7 = 4,478,976 possible orientations
   * (4,478,976/2/1024^2 = 2.13MB of storage).
   */
  OrientationPatternDatabase::OrientationPatternDatabase() : PatternDatabase(479001600)
  {
    for (unsigned i = 0; i < 4096; ++i)
    {
      bitset<12> bits(i);
      this->onesCountLookup[i] = bits.count();
    }
  }

  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t OrientationPatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCubeIndexModel::EDGE EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // The permutation of the 12 edges.
    perm_t edgePerm;

    for (unsigned i = 0; i < 12; ++i)
      edgePerm[i] = iCube.getEdgeIndex((EDGE)i);

    perm_t lehmer;
    bitset<12> seen;

    lehmer[0] = edgePerm[0];
    seen[11 - edgePerm[0]] = 1;
    lehmer[11] = 0;

    for (unsigned i = 1; i < 11; ++i)
    {
      // std::bitset indexes right-to-left.
      seen[11 - edgePerm[i]] = 1;

      uint8_t numOnes = this->onesCountLookup[seen.to_ulong() >> (12 - edgePerm[i])];

      lehmer[i] = edgePerm[i] - numOnes;
    }

    return
      lehmer[0] * 39916800 +
      lehmer[1] * 3628800 +
      lehmer[2] * 362880 +
      lehmer[3] * 40320 +
      lehmer[4] * 5040 +
      lehmer[5] * 720 +
      lehmer[6] * 120 +
      lehmer[7] * 24 +
      lehmer[8] * 6 +
      lehmer[9] * 2 +
      lehmer[10];
  }
}

