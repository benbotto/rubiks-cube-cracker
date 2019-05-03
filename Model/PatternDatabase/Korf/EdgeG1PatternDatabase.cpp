#include "EdgeG1PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG1PatternDatabase::getDatabaseIndex(const RubiksCubeModel& cube) const
  {
    // UB RY 0.
    edge_t ub = {cube.get(1), cube.get(33)};

    // UR RG 1.
    edge_t ur = {cube.get(3), cube.get(25)};

    // UF RW 2.
    edge_t uf = {cube.get(5), cube.get(17)};

    // UL RB 3.
    edge_t ul = {cube.get(7), cube.get(9)};

    // FR WG 4.
    edge_t fr = {cube.get(19), cube.get(31)};

    // FL WB 5.
    edge_t fl = {cube.get(23), cube.get(11)};

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
    array<uint8_t, 6> edgeOrientations =
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

