#ifndef _BUSYBIN_G3_PATTERN_DATABASE_H_
#define _BUSYBIN_G3_PATTERN_DATABASE_H_

#include "../PatternDatabase.h"
#include "../CombinationIndexer.h"
#include "../UnorderedPairSetIndexer.h"
#include "../../RubiksCube.h"
#include "../../RubiksCubeIndexModel.h"
#include "../PatternDatabase.h"
#include <cstdint>
#include <array>
using std::array;

namespace busybin
{
  /**
   * A pattern database that holds positions of the 8 corners as diagonal
   * tetrad pairs, {ULB, URF}, {DLF, DRB}, {URB, ULF}, {DLB, DRF}.  In
   * Thistlethwaite's algorithm he ensures that corners are in their tetrads
   * and that the total tetrad twist is fixed (solvable with only half moves),
   * but this indexes pairs of corners which is simpler and still solvable with
   * half twists.
   *
   * This DB also holds the positions of the 4 edges in the M slice (FU, FD,
   * BU, BD), and the parity of the corners.
   *
   * See Stefan Pochmann's solver, since this uses his G3 criteria:
   * https://www.stefan-pochmann.info/spocc/other_stuff/tools/solver_thistlethwaite/solver_thistlethwaite_cpp.txt
   *
   * Used for moving from G2->G3 using the Thistlethwaite algorithm.
   */
  class G3PatternDatabase : public PatternDatabase
  {
    CombinationIndexer<8, 4> comboIndexer;
    UnorderedPairSetIndexer<8> pairSetIndexer;

    void getTetradPair(
      const RubiksCubeIndexModel& iCube,
      array<uint8_t, 2>& tetradPair,
      RubiksCube::CORNER c1,
      RubiksCube::CORNER c2
    ) const;

  public:
    G3PatternDatabase();
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif
