#include "GoalG2_G3.h"

namespace busybin
{
  /**
   * Pair all tetrad corners {ULB, URF}, {DLF, DRB}, {URB, ULF}, {DLB, DRF},
   * which makes the corners solvable with only half twists.  (Thistlethwaite's
   * algorithm puts the corners in the tetrads, ensures the parity is even, and
   * fixes the tetrad twists, but that's difficult and slow to index.)
   *
   * This also ensures all edges are in their slices.  Since the E-slice edges
   * are already positioned in G2, this only positions the M-slice edges, {UF,
   * UB, DF, DB}.  The S-slice edges naturally fall into place.
   *
   * Lastly, this ensures that the parity of the corners is even.  The parity
   * of corners and edges is bound, so if the corner parity is even, so is the
   * edge parity.
   *
   * @param cube The cube.
   */
  bool GoalG2_G3::isSatisfied(RubiksCube& cube)
  {
    typedef RubiksCube::CORNER CORNER;
    typedef RubiksCube::EDGE   EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // If any corner is not paired, return false.
    uint8_t cornerInd;

    // {ULB, URF} pair.
    cornerInd = iCube.getCornerIndex(CORNER::ULB);
    if (cornerInd != (uint8_t)CORNER::ULB && cornerInd != (uint8_t)CORNER::URF)
      return false;

    cornerInd = iCube.getCornerIndex(CORNER::URF);
    if (cornerInd != (uint8_t)CORNER::ULB && cornerInd != (uint8_t)CORNER::URF)
      return false;

    // {DLF, DRB} pair.
    cornerInd = iCube.getCornerIndex(CORNER::DLF);
    if (cornerInd != (uint8_t)CORNER::DLF && cornerInd != (uint8_t)CORNER::DRB)
      return false;

    cornerInd = iCube.getCornerIndex(CORNER::DRB);
    if (cornerInd != (uint8_t)CORNER::DLF && cornerInd != (uint8_t)CORNER::DRB)
      return false;

    // If three sets of corners are paired, the last ({DLB, DRF}) must be, too.

    // The 4 edges M-slice edges.
    const array<EDGE, 4> edges = {EDGE::UB, EDGE::UF, EDGE::DF, EDGE::DB};

    for (unsigned i = 0; i < 4; ++i)
    {
      uint8_t edgeInd = iCube.getEdgeIndex(edges[i]);

      // If any edge in the M slice is not an M-slice edge, return false.
      if (
        edgeInd != (uint8_t)edges[0] &&
        edgeInd != (uint8_t)edges[1] &&
        edgeInd != (uint8_t)edges[2] &&
        edgeInd != (uint8_t)edges[3]
      )
        return false;
    }

    // Parity must be even.  See G3PatternDatabase.cpp for an explanation.
    const uint8_t numCorners = 8;
    uint8_t parity = 0;

    for (uint8_t i = 0; i < numCorners; ++i)
      for (uint8_t j = i + 1; j < numCorners; ++j)
        parity ^= iCube.getCornerIndex((CORNER)i) < iCube.getCornerIndex((CORNER)j);

    return parity == 0;
  }

  /**
   * Describe the goal.
   */
  string GoalG2_G3::getDescription() const
  {
    return "Pair all tetrad corners and get all edges in the correct slices.";
  }
}
