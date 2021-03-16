#include "G4PatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage.
   *
   * For the edges, the 4 edges in each slice can be permuted in any of 4!
   * ways, giving 4!^3.  However, the edge parity is fixed in G3, so only half
   * of those states are reachable.  Put another way, if 10 edges are solved,
   * the other two must be solved because it's not possible to make just one
   * swap (swap two edges).  The indexing here stores the permutations of the M
   * and S slices, and two of the 4 edges in the E slice: 4!*4!*4P2 = 6912.
   *
   * Like the edges, the corners have even parity in G3, which means that only
   * half of the corner 4!^2 permutations are reachable.  But further, corners
   * have "fixed tetrad twists," which means that 3-cycle twists of the corners
   * are not possible with only half twists.  Said differently, it's not
   * possible for 3 oriented corners to be out of place.  That means that
   * 4!*4!/(2*3) = 96 corner permutations are reachable.  For indexing, this
   * stores the permutation of the first tetrad, and the index of one piece in
   * the other tetrad:  4! * 4P1 = 96.
   *
   * 6912 * 96 / 1024^2 / 2 = 663552 / 1024^2 / 2 = ~.32MB on disk.
   */
  G4PatternDatabase::G4PatternDatabase() : PatternDatabase(663552)
  {
  }

  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t G4PatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCube::CORNER CORNER;
    typedef RubiksCube::EDGE   EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // This maps the edges in each slice to sequential indexes.
    array<uint8_t, 12> edgeMap;

    // M slice.
    edgeMap[(unsigned)EDGE::UB] = 0;
    edgeMap[(unsigned)EDGE::UF] = 1;
    edgeMap[(unsigned)EDGE::DF] = 2;
    edgeMap[(unsigned)EDGE::DB] = 3;

    // S slice.
    edgeMap[(unsigned)EDGE::UR] = 0;
    edgeMap[(unsigned)EDGE::UL] = 1;
    edgeMap[(unsigned)EDGE::DL] = 2;
    edgeMap[(unsigned)EDGE::DR] = 3;

    // E slice.
    edgeMap[(unsigned)EDGE::FR] = 0;
    edgeMap[(unsigned)EDGE::FL] = 1;
    edgeMap[(unsigned)EDGE::BL] = 2;
    edgeMap[(unsigned)EDGE::BR] = 3;

    array<uint8_t, 4> m = {{
      edgeMap[iCube.getEdgeIndex(EDGE::UB)],
      edgeMap[iCube.getEdgeIndex(EDGE::UF)],
      edgeMap[iCube.getEdgeIndex(EDGE::DF)],
      edgeMap[iCube.getEdgeIndex(EDGE::DB)],
    }};

    array<uint8_t, 4> s = {{
      edgeMap[iCube.getEdgeIndex(EDGE::UR)],
      edgeMap[iCube.getEdgeIndex(EDGE::UL)],
      edgeMap[iCube.getEdgeIndex(EDGE::DL)],
      edgeMap[iCube.getEdgeIndex(EDGE::DR)],
    }};

    array<uint8_t, 2> e = {{
      edgeMap[iCube.getEdgeIndex(EDGE::FR)],
      edgeMap[iCube.getEdgeIndex(EDGE::FL)],
    }};

    uint32_t mRank = this->permIndexer.rank(m);
    uint32_t sRank = this->permIndexer.rank(s);
    uint32_t eRank = this->partialPermIndexer.rank(e);

    // 4! * 4P2 = 288.  4P2 = 12.
    uint32_t edgeRank = mRank * 288 + sRank * 12 + eRank;

    // This maps the corners in each tetrad to sequential indexes.
    array<uint8_t, 8> cornerMap;

    // First tetrad.
    cornerMap[(unsigned)CORNER::ULB] = 0;
    cornerMap[(unsigned)CORNER::URF] = 1;
    cornerMap[(unsigned)CORNER::DLF] = 2;
    cornerMap[(unsigned)CORNER::DRB] = 3;

    // Second tetrad.
    cornerMap[(unsigned)CORNER::URB] = 0;
    cornerMap[(unsigned)CORNER::ULF] = 1;
    cornerMap[(unsigned)CORNER::DLB] = 2;
    cornerMap[(unsigned)CORNER::DRF] = 3;

    array<uint8_t, 4> tetrad1 = {{
      cornerMap[iCube.getCornerIndex(CORNER::ULB)],
      cornerMap[iCube.getCornerIndex(CORNER::URF)],
      cornerMap[iCube.getCornerIndex(CORNER::DLF)],
      cornerMap[iCube.getCornerIndex(CORNER::DRB)],
    }};

    // Arbitrarily, the URB corner from the second tetrad is used.
    uint8_t urb = cornerMap[iCube.getCornerIndex(CORNER::URB)];

    uint32_t tetrad1Rank = this->permIndexer.rank(tetrad1);

    uint32_t cornerRank = tetrad1Rank * 4 + urb;

    // 4! * 4 = 96 (or 4!4!/(2*3)).
    return edgeRank * 96 + cornerRank;
  }
}
