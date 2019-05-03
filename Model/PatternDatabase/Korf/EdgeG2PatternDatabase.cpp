#include "EdgeG2PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG2PatternDatabase::getDatabaseIndex(const RubiksCubeModel& cube) const
  {
    // BL YB 6.
    edge_t bl = {cube.get(35), cube.get(15)};

    // BR YG 7.
    edge_t br = {cube.get(39), cube.get(27)};

    // DF OW 8.
    edge_t df = {cube.get(41), cube.get(21)};

    // DL OB 9.
    edge_t dl = {cube.get(47), cube.get(13)};

    // DB OY 10.
    edge_t db = {cube.get(45), cube.get(37)};

    // DR OG 11.
    edge_t dr = {cube.get(43), cube.get(29)};

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

