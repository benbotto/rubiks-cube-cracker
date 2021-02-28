#include "TestPatternDatabase.h"

namespace busybin
{
  /**
   * All arrangements of the 8 edge cubies in the E and S slices are reachable,
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

    // This maps the edges in the E and S slices to sequential indexes.  Edges
    // in the M slice are ignored since they cannot be moved out of the M slice
    // with G2 twists (no quarter turns of F or B).
    array<uint8_t, 12> edgeMap;

    //edgeMap[(unsigned)EDGE::UB] = 15;
    edgeMap[(unsigned)EDGE::UR] = 0;
    //edgeMap[(unsigned)EDGE::UF] = 15;
    edgeMap[(unsigned)EDGE::UL] = 1;
    edgeMap[(unsigned)EDGE::FR] = 2;
    edgeMap[(unsigned)EDGE::FL] = 3;
    edgeMap[(unsigned)EDGE::BL] = 4;
    edgeMap[(unsigned)EDGE::BR] = 5;
    //edgeMap[(unsigned)EDGE::DF] = 15;
    edgeMap[(unsigned)EDGE::DL] = 6;
    //edgeMap[(unsigned)EDGE::DB] = 15;
    edgeMap[(unsigned)EDGE::DR] = 7;

    array<uint8_t, 8> edgeIndexes =
    {
      edgeMap[iCube.getEdgeIndex(EDGE::UR)],
      edgeMap[iCube.getEdgeIndex(EDGE::UL)],
      edgeMap[iCube.getEdgeIndex(EDGE::FR)],
      edgeMap[iCube.getEdgeIndex(EDGE::FL)],
      edgeMap[iCube.getEdgeIndex(EDGE::BL)],
      edgeMap[iCube.getEdgeIndex(EDGE::BR)],
      edgeMap[iCube.getEdgeIndex(EDGE::DL)],
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

