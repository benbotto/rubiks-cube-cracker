#include "G3PatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage.
   *
   * For tetrad-paired corners, each pair is unique and is a combination.
   * There are 8 corners, so there are 4 pairs of corner combinations.  The
   * corners therefore need 8C2*6C2*4C2 = 2520 elements.
   *
   * For the four edges, there are 8C4 combinations: 4 edges and 8 positions
   * (the E-slice edges are positioned in G2), and the order does not matter.
   * This arbitrarily uses the M-slice edges for indexing.  S-slice edges
   * naturally fall into position.
   *
   * The parity is also stored.  Parity of corners and edges is bound--when the
   * edge parity is even, so is the corner parity.  This doubles the number of
   * elements--the last bit in the index is used for parity, 0 for even, 1 for
   * odd.
   *
   * 70 * 2520 * 2 / 1024^2 / 2 = 352800 / 1024^2 / 2 = ~.17MB on disk.
   */
  G3PatternDatabase::G3PatternDatabase() : PatternDatabase(352800)
  {
  }

  /**
   * Private helper to find the positions of a pair of corners.  The corners'
   * positions are set on the tetradPair argument in ascending order.
   */
  void G3PatternDatabase::getTetradPair(
    const RubiksCubeIndexModel& iCube,
    array<uint8_t, 2>& tetradPair,
    RubiksCube::CORNER c1,
    RubiksCube::CORNER c2
  ) const
  {
    typedef RubiksCube::CORNER CORNER;

    const uint8_t numCorners = 8;
    unsigned comboInd = 0;

    for (uint8_t i = 0; i < numCorners && comboInd < 2; ++i)
    {
      uint8_t cornerInd = iCube.getCornerIndex((CORNER)i);

      if (cornerInd == (uint8_t)c1 || cornerInd == (uint8_t)c2)
        tetradPair[comboInd++] = i;
    }
  }

  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t G3PatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCube::EDGE   EDGE;
    typedef RubiksCube::CORNER CORNER;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);
    const uint8_t numEdges   = 12;
    const uint8_t numCorners = 8;

    // Rank the tetrad pairs as pairs of combinations (a set partitioned into
    // unordered subsets of size 2).
    array<array<uint8_t, 2>, 4> tetradPairs;

    this->getTetradPair(iCube, tetradPairs[0], CORNER::ULB, CORNER::URF);
    this->getTetradPair(iCube, tetradPairs[1], CORNER::DLF, CORNER::DRB);
    this->getTetradPair(iCube, tetradPairs[2], CORNER::URB, CORNER::ULF);
    this->getTetradPair(iCube, tetradPairs[3], CORNER::DLB, CORNER::DRF);

    uint32_t cornerRank = this->pairSetIndexer.rank(tetradPairs);

    // This maps the edges in the M and S slices to sequential indexes.  Edges
    // in the E slice are ignored since they cannot be moved out of the E slice
    // with G2 twists (no quarter turns of F/B/L/R).
    array<uint8_t, 12> edgeMap;

    edgeMap[(unsigned)EDGE::UB] = 0;
    edgeMap[(unsigned)EDGE::UR] = 1;
    edgeMap[(unsigned)EDGE::UF] = 2;
    edgeMap[(unsigned)EDGE::UL] = 3;
    edgeMap[(unsigned)EDGE::DF] = 4;
    edgeMap[(unsigned)EDGE::DL] = 5;
    edgeMap[(unsigned)EDGE::DB] = 6;
    edgeMap[(unsigned)EDGE::DR] = 7;

    // Find the position that each M-slice edge is occupying, and map the
    // positions to sequential numbers [0..7].  edgeCombo holds these position
    // indexes in ascending order so that the set can be ranked as an 8C4
    // combination.
    array<uint8_t, 4> edgeCombo;
    unsigned edgeComboInd = 0;

    for (uint8_t i = 0; i < numEdges && edgeComboInd < 4; ++i)
    {
      uint8_t edgeInd = iCube.getEdgeIndex((EDGE)i);

      if (
        edgeInd == (uint8_t)EDGE::UB ||
        edgeInd == (uint8_t)EDGE::UF ||
        edgeInd == (uint8_t)EDGE::DF ||
        edgeInd == (uint8_t)EDGE::DB
      )
        edgeCombo[edgeComboInd++] = edgeMap[i];
    }

    uint32_t edgeRank = this->comboIndexer.rank(edgeCombo);

    // Parity of the corners.  This uses the same logic as a bubble sort would
    // to count the number of swaps needed, but toggles a boolean back and
    // forth to keep track of whether the number of swaps required to sort the
    // array of corner indexes is even or odd.
    uint8_t parity = 0;

    for (uint8_t i = 0; i < numCorners; ++i)
      for (uint8_t j = i + 1; j < numCorners; ++j)
        parity ^= iCube.getCornerIndex((CORNER)i) < iCube.getCornerIndex((CORNER)j);

    // 2520 = 8C2*6C2*4C2.
    return (edgeRank * 2520 + cornerRank) * 2 + parity;
  }
}
