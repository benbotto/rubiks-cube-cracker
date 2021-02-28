#include "TestPatternDatabase.h"

namespace busybin
{
  /**
   * All arrangements of the 8 edge cubies in the M and S slices are reachable,
   * so there are 8! = 40320 permutations.
   */
  TestPatternDatabase::TestPatternDatabase() : PatternDatabase(40320)
  {
  }

  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t TestPatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    typedef RubiksCubeIndexModel::EDGE EDGE;

    const RubiksCubeIndexModel& iCube = static_cast<const RubiksCubeIndexModel&>(cube);

    // This maps the edges in the M and S slices to sequential indexes.  Edges
    // in the E slice are ignored since they cannot be moved out of the E slice
    // with G2 twists (no quarter turns of F/B/L/R).
    array<uint8_t, 12> edgeMap;

    edgeMap[(unsigned)EDGE::UB] = 0;
    edgeMap[(unsigned)EDGE::UR] = 1;
    edgeMap[(unsigned)EDGE::UF] = 2;
    edgeMap[(unsigned)EDGE::UL] = 3;
    //edgeMap[(unsigned)EDGE::FR] = 15;
    //edgeMap[(unsigned)EDGE::FL] = 15;
    //edgeMap[(unsigned)EDGE::BL] = 15;
    //edgeMap[(unsigned)EDGE::BR] = 15;
    edgeMap[(unsigned)EDGE::DF] = 4;
    edgeMap[(unsigned)EDGE::DL] = 5;
    edgeMap[(unsigned)EDGE::DB] = 6;
    edgeMap[(unsigned)EDGE::DR] = 7;

    array<uint8_t, 8> edgeIndexes =
    {
      edgeMap[iCube.getEdgeIndex(EDGE::UB)],
      edgeMap[iCube.getEdgeIndex(EDGE::UR)],
      edgeMap[iCube.getEdgeIndex(EDGE::UF)],
      edgeMap[iCube.getEdgeIndex(EDGE::UL)],
      edgeMap[iCube.getEdgeIndex(EDGE::DF)],
      edgeMap[iCube.getEdgeIndex(EDGE::DL)],
      edgeMap[iCube.getEdgeIndex(EDGE::DB)],
      edgeMap[iCube.getEdgeIndex(EDGE::DR)]
    };

    //for (unsigned i = 0; i < 8; ++i)
    //  cout << (unsigned)edgeIndexes[i] << ' ';
    //cout << endl;

    uint32_t rank = this->permIndexer.rank(edgeIndexes);

    //cout << "Rank: " << rank << endl;

    return rank;
  }
}

