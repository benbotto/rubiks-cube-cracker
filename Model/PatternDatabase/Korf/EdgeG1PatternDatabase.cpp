#include "EdgeG1PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG1PatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    const RubiksCubeModel& cubeModel = static_cast<const RubiksCubeModel&>(cube);

    // UB RY 0.
    edge_t ub = {cubeModel.getColor(1), cubeModel.getColor(33)};

    // UR RG 1.
    edge_t ur = {cubeModel.getColor(3), cubeModel.getColor(25)};

    // UF RW 2.
    edge_t uf = {cubeModel.getColor(5), cubeModel.getColor(17)};

    // UL RB 3.
    edge_t ul = {cubeModel.getColor(7), cubeModel.getColor(9)};

    // FR WG 4.
    edge_t fr = {cubeModel.getColor(19), cubeModel.getColor(31)};

    // FL WB 5.
    edge_t fl = {cubeModel.getColor(23), cubeModel.getColor(11)};

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

