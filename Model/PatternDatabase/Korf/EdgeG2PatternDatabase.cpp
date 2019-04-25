#include "EdgeG2PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG2PatternDatabase::getDatabaseIndex(const RubiksCubeModel& cube) const
  {
    // BL YB 6.
    edge_t bl =
    {
      cube.get(F::BACK, 1, 2),
      cube.get(F::LEFT, 1, 0)
    };

    // BR YG 7.
    edge_t br =
    {
      cube.get(F::BACK,  1, 0),
      cube.get(F::RIGHT, 1, 2)
    };

    // DF OW 8.
    edge_t df =
    {
      cube.get(F::DOWN,  0, 1),
      cube.get(F::FRONT, 2, 1)
    };

    // DL OB 9.
    edge_t dl =
    {
      cube.get(F::DOWN, 1, 0),
      cube.get(F::LEFT, 2, 1)
    };

    // DB OY 10.
    edge_t db =
    {
      cube.get(F::DOWN, 2, 1),
      cube.get(F::BACK, 2, 1)
    };

    // DR OG 11.
    edge_t dr =
    {
      cube.get(F::DOWN,  1, 2),
      cube.get(F::RIGHT, 2, 1)
    };

    perm_t edgePerm =
    {
      this->getCubieIndex(bl),
      this->getCubieIndex(br),
      this->getCubieIndex(df),
      this->getCubieIndex(dl),
      this->getCubieIndex(db),
      this->getCubieIndex(dr)
    };

    // Now get the orientation of each edge.
    array<uchar, 6> edgeOrientations =
    {
      this->getCubieOrientation(bl),
      this->getCubieOrientation(br),
      this->getCubieOrientation(df),
      this->getCubieOrientation(dl),
      this->getCubieOrientation(db),
      this->getCubieOrientation(dr)
    };

    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

