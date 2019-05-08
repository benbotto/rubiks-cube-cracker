#include "EdgeG2PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG2PatternDatabase::getDatabaseIndex(const RubiksCubeModel& cube) const
  {
    // BL YB 6.
    edge_t bl = {cube.getColor(35), cube.getColor(15)};

    // BR YG 7.
    edge_t br = {cube.getColor(39), cube.getColor(27)};

    // DF OW 8.
    edge_t df = {cube.getColor(41), cube.getColor(21)};

    // DL OB 9.
    edge_t dl = {cube.getColor(47), cube.getColor(13)};

    // DB OY 10.
    edge_t db = {cube.getColor(45), cube.getColor(37)};

    // DR OG 11.
    edge_t dr = {cube.getColor(43), cube.getColor(29)};

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
    array<uint8_t, 6> edgeOrientations =
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

