#include "EdgeG2PatternDatabase.h"

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG2PatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
  {
    const RubiksCubeModel& cubeModel = static_cast<const RubiksCubeModel&>(cube);

    // BL YB 6.
    edge_t bl = {cubeModel.getColor(35), cubeModel.getColor(15)};

    // BR YG 7.
    edge_t br = {cubeModel.getColor(39), cubeModel.getColor(27)};

    // DF OW 8.
    edge_t df = {cubeModel.getColor(41), cubeModel.getColor(21)};

    // DL OB 9.
    edge_t dl = {cubeModel.getColor(47), cubeModel.getColor(13)};

    // DB OY 10.
    edge_t db = {cubeModel.getColor(45), cubeModel.getColor(37)};

    // DR OG 11.
    edge_t dr = {cubeModel.getColor(43), cubeModel.getColor(29)};

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

