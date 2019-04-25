#include "EdgeG1PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG1PatternDatabase::getDatabaseIndex(const RubiksCubeModel& cube) const
  {
    // UB RY 0.
    edge_t ub =
    {
      cube.get(F::UP,   0, 1),
      cube.get(F::BACK, 0, 1)
    };

    // UR RG 1.
    edge_t ur =
    {
      cube.get(F::UP,    1, 2),
      cube.get(F::RIGHT, 0, 1)
    };

    // UF RW 2.
    edge_t uf =
    {
      cube.get(F::UP,    2, 1),
      cube.get(F::FRONT, 0, 1)
    };

    // UL RB 3.
    edge_t ul =
    {
      cube.get(F::UP,   1, 0),
      cube.get(F::LEFT, 0, 1)
    };

    // FR WG 4.
    edge_t fr =
    {
      cube.get(F::FRONT, 1, 2),
      cube.get(F::RIGHT, 1, 0)
    };

    // FL WB 5.
    edge_t fl =
    {
      cube.get(F::FRONT, 1, 0),
      cube.get(F::LEFT,  1, 2)
    };

    perm_t edgePerm =
    {
      this->getCubieIndex(ub),
      this->getCubieIndex(ur),
      this->getCubieIndex(uf),
      this->getCubieIndex(ul),
      this->getCubieIndex(fr),
      this->getCubieIndex(fl)
    };

    // Now get the orientation of each edge.
    array<uchar, 6> edgeOrientations =
    {
      this->getCubieOrientation(ub),
      this->getCubieOrientation(ur),
      this->getCubieOrientation(uf),
      this->getCubieOrientation(ul),
      this->getCubieOrientation(fr),
      this->getCubieOrientation(fl)
    };

    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

