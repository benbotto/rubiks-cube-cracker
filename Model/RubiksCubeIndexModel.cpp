#include "RubiksCubeIndexModel.h"

namespace busybin
{
  /**
   * Initialize the cube with red on the top and white up front.  Note that the
   * orientation matches the solver, not the RubiksCubeModel.
   */
  RubiksCubeIndexModel::RubiksCubeIndexModel()
  {
    // Edges.
    for (unsigned i = 0; i < 12; ++i)
    {
      this->edges[i].index       = i;
      this->edges[i].orientation = 0;
    }

    // Corners.
    for (unsigned i = 0; i < 8; ++i)
    {
      this->corners[i].index       = i;
      this->corners[i].orientation = 0;
    }

    // Centers.
    this->centers[0] = COLOR::RED;
    this->centers[1] = COLOR::BLUE;
    this->centers[2] = COLOR::WHITE;
    this->centers[3] = COLOR::GREEN;
    this->centers[4] = COLOR::YELLOW;
    this->centers[5] = COLOR::ORANGE;
  }

  /**
   * Construct from a RubiksCubeModel.
   */
  RubiksCubeIndexModel::RubiksCubeIndexModel(const RubiksCubeModel& cube)
  {
    if (cube.getColor(FACE::UP, 1, 1) != COLOR::RED ||
      cube.getColor(FACE::FRONT, 1, 1) != COLOR::WHITE)
    {
      throw RubiksCubeException(
        "RubiksCubeIndexModel can only be initialized from a model if it's oriented with red on top and white up front.");
    }

    // Corners.
    typedef RubiksCubeModel::corner_t corner_t;

    corner_t ulb = {cube.getColor(0), cube.getColor(8), cube.getColor(34)};
    this->corners[(unsigned)CORNER::ULB].index       = cube.getCornerIndex(ulb);
    this->corners[(unsigned)CORNER::ULB].orientation = cube.getCornerOrientation(ulb);

    corner_t urb = {cube.getColor(2), cube.getColor(26), cube.getColor(32)};
    this->corners[(unsigned)CORNER::URB].index       = cube.getCornerIndex(urb);
    this->corners[(unsigned)CORNER::URB].orientation = cube.getCornerOrientation(urb);

    corner_t urf = {cube.getColor(4), cube.getColor(24), cube.getColor(18)};
    this->corners[(unsigned)CORNER::URF].index       = cube.getCornerIndex(urf);
    this->corners[(unsigned)CORNER::URF].orientation = cube.getCornerOrientation(urf);

    corner_t ulf = {cube.getColor(6), cube.getColor(10), cube.getColor(16)};
    this->corners[(unsigned)CORNER::ULF].index       = cube.getCornerIndex(ulf);
    this->corners[(unsigned)CORNER::ULF].orientation = cube.getCornerOrientation(ulf);

    corner_t dlf = {cube.getColor(40), cube.getColor(12), cube.getColor(22)};
    this->corners[(unsigned)CORNER::DLF].index       = cube.getCornerIndex(dlf);
    this->corners[(unsigned)CORNER::DLF].orientation = cube.getCornerOrientation(dlf);

    corner_t dlb = {cube.getColor(46), cube.getColor(14), cube.getColor(36)};
    this->corners[(unsigned)CORNER::DLB].index       = cube.getCornerIndex(dlb);
    this->corners[(unsigned)CORNER::DLB].orientation = cube.getCornerOrientation(dlb);

    corner_t drb = {cube.getColor(44), cube.getColor(28), cube.getColor(38)};
    this->corners[(unsigned)CORNER::DRB].index       = cube.getCornerIndex(drb);
    this->corners[(unsigned)CORNER::DRB].orientation = cube.getCornerOrientation(drb);

    corner_t drf = {cube.getColor(42), cube.getColor(30), cube.getColor(20)};
    this->corners[(unsigned)CORNER::DRF].index       = cube.getCornerIndex(drf);
    this->corners[(unsigned)CORNER::DRF].orientation = cube.getCornerOrientation(drf);

    // Edges.
    typedef RubiksCubeModel::edge_t edge_t;

    edge_t ub = {cube.getColor(1), cube.getColor(33)};
    this->edges[(unsigned)EDGE::UB].index       = cube.getEdgeIndex(ub);
    this->edges[(unsigned)EDGE::UB].orientation = cube.getEdgeOrientation(ub);

    edge_t ur = {cube.getColor(3), cube.getColor(25)};
    this->edges[(unsigned)EDGE::UR].index       = cube.getEdgeIndex(ur);
    this->edges[(unsigned)EDGE::UR].orientation = cube.getEdgeOrientation(ur);

    edge_t uf = {cube.getColor(5), cube.getColor(17)};
    this->edges[(unsigned)EDGE::UF].index       = cube.getEdgeIndex(uf);
    this->edges[(unsigned)EDGE::UF].orientation = cube.getEdgeOrientation(uf);

    edge_t ul = {cube.getColor(7), cube.getColor(9)};
    this->edges[(unsigned)EDGE::UL].index       = cube.getEdgeIndex(ul);
    this->edges[(unsigned)EDGE::UL].orientation = cube.getEdgeOrientation(ul);

    edge_t fr = {cube.getColor(19), cube.getColor(31)};
    this->edges[(unsigned)EDGE::FR].index       = cube.getEdgeIndex(fr);
    this->edges[(unsigned)EDGE::FR].orientation = cube.getEdgeOrientation(fr);

    edge_t fl = {cube.getColor(23), cube.getColor(11)};
    this->edges[(unsigned)EDGE::FL].index       = cube.getEdgeIndex(fl);
    this->edges[(unsigned)EDGE::FL].orientation = cube.getEdgeOrientation(fl);

    edge_t bl = {cube.getColor(35), cube.getColor(15)};
    this->edges[(unsigned)EDGE::BL].index       = cube.getEdgeIndex(bl);
    this->edges[(unsigned)EDGE::BL].orientation = cube.getEdgeOrientation(bl);

    edge_t br = {cube.getColor(39), cube.getColor(27)};
    this->edges[(unsigned)EDGE::BR].index       = cube.getEdgeIndex(br);
    this->edges[(unsigned)EDGE::BR].orientation = cube.getEdgeOrientation(br);

    edge_t df = {cube.getColor(41), cube.getColor(21)};
    this->edges[(unsigned)EDGE::DF].index       = cube.getEdgeIndex(df);
    this->edges[(unsigned)EDGE::DF].orientation = cube.getEdgeOrientation(df);

    edge_t dl = {cube.getColor(47), cube.getColor(13)};
    this->edges[(unsigned)EDGE::DL].index       = cube.getEdgeIndex(dl);
    this->edges[(unsigned)EDGE::DL].orientation = cube.getEdgeOrientation(dl);

    edge_t db = {cube.getColor(45), cube.getColor(37)};
    this->edges[(unsigned)EDGE::DB].index       = cube.getEdgeIndex(db);
    this->edges[(unsigned)EDGE::DB].orientation = cube.getEdgeOrientation(db);

    edge_t dr = {cube.getColor(43), cube.getColor(29)};
    this->edges[(unsigned)EDGE::DR].index       = cube.getEdgeIndex(dr);
    this->edges[(unsigned)EDGE::DR].orientation = cube.getEdgeOrientation(dr);

    // Centers.
    this->centers[0] = COLOR::RED;
    this->centers[1] = COLOR::BLUE;
    this->centers[2] = COLOR::WHITE;
    this->centers[3] = COLOR::GREEN;
    this->centers[4] = COLOR::YELLOW;
    this->centers[5] = COLOR::ORANGE;
  }

  /**
   * Get the edge colors at an index.
   */
  array<RubiksCubeIndexModel::COLOR, 2> RubiksCubeIndexModel::getEdgeColors(
    RubiksCubeIndexModel::EDGE ind) const
  {
    array<COLOR, 2> colors;

    Cubie edge = this->edges.at((unsigned)ind);

    switch ((EDGE)edge.index)
    {
      case EDGE::UB:
        colors[0] = COLOR::RED;
        colors[1] = COLOR::YELLOW;
        break;

      case EDGE::UR:
        colors[0] = COLOR::RED;
        colors[1] = COLOR::GREEN;
        break;

      case EDGE::UF:
        colors[0] = COLOR::RED;
        colors[1] = COLOR::WHITE;
        break;

      case EDGE::UL:
        colors[0] = COLOR::RED;
        colors[1] = COLOR::BLUE;
        break;

      case EDGE::FR:
        colors[0] = COLOR::WHITE;
        colors[1] = COLOR::GREEN;
        break;

      case EDGE::FL:
        colors[0] = COLOR::WHITE;
        colors[1] = COLOR::BLUE;
        break;

      case EDGE::BL:
        colors[0] = COLOR::YELLOW;
        colors[1] = COLOR::BLUE;
        break;

      case EDGE::BR:
        colors[0] = COLOR::YELLOW;
        colors[1] = COLOR::GREEN;
        break;

      case EDGE::DF:
        colors[0] = COLOR::ORANGE;
        colors[1] = COLOR::WHITE;
        break;

      case EDGE::DL:
        colors[0] = COLOR::ORANGE;
        colors[1] = COLOR::BLUE;
        break;

      case EDGE::DB:
        colors[0] = COLOR::ORANGE;
        colors[1] = COLOR::YELLOW;
        break;

      case EDGE::DR:
        colors[0] = COLOR::ORANGE;
        colors[1] = COLOR::GREEN;
        break;
    }

    if (edge.orientation == 1)
      swap(colors[0], colors[1]);

    return colors;
  }

  /**
   * Get the corner colors at an index.  Three colors are returns: U or D, L or
   * R, F or B (YXZ).
   */
  array<RubiksCubeIndexModel::COLOR, 3> RubiksCubeIndexModel::getCornerColors(
    RubiksCubeIndexModel::CORNER ind) const
  {
    array<COLOR, 3> colors;

    Cubie corner = this->corners.at((unsigned)ind);

    unsigned i0, i1, i2;

    // Red or orange on top.
    if (corner.orientation == 0)
    {
      i0 = 0;
      i1 = 1;
      i2 = 2;

      // A quarter turn of U or D swaps the two other colors.
      if ((corner.index + (unsigned)ind) % 2 == 1)
        swap(i1, i2);
    }
    else if (corner.orientation == 1)
    {
      i0 = 1;
      i1 = 2;
      i2 = 0;

      if ((corner.index + (unsigned)ind) % 2 == 1)
        swap(i0, i1);
    }
    else // if (corner.orientation == 2)
    {
      i0 = 2;
      i1 = 0;
      i2 = 1;

      if ((corner.index + (unsigned)ind) % 2 == 1)
        swap(i0, i2);
    }

    switch ((CORNER)corner.index)
    {
      case CORNER::ULB:
        colors[i0] = COLOR::RED;
        colors[i1] = COLOR::BLUE;
        colors[i2] = COLOR::YELLOW;
        break;

      case CORNER::URB:
        colors[i0] = COLOR::RED;
        colors[i1] = COLOR::GREEN;
        colors[i2] = COLOR::YELLOW;
        break;

      case CORNER::URF:
        colors[i0] = COLOR::RED;
        colors[i1] = COLOR::GREEN;
        colors[i2] = COLOR::WHITE;
        break;

      case CORNER::ULF:
        colors[i0] = COLOR::RED;
        colors[i1] = COLOR::BLUE;
        colors[i2] = COLOR::WHITE;
        break;

      case CORNER::DLF:
        colors[i0] = COLOR::ORANGE;
        colors[i1] = COLOR::BLUE;
        colors[i2] = COLOR::WHITE;
        break;

      case CORNER::DLB:
        colors[i0] = COLOR::ORANGE;
        colors[i1] = COLOR::BLUE;
        colors[i2] = COLOR::YELLOW;
        break;

      case CORNER::DRB:
        colors[i0] = COLOR::ORANGE;
        colors[i1] = COLOR::GREEN;
        colors[i2] = COLOR::YELLOW;
        break;

      case CORNER::DRF:
        colors[i0] = COLOR::ORANGE;
        colors[i1] = COLOR::GREEN;
        colors[i2] = COLOR::WHITE;
        break;
    }

    return colors;
  }

  /**
   * Get the facet color using a face, row, and column.
   */
  RubiksCubeIndexModel::COLOR RubiksCubeIndexModel::getColor(
    FACE f, unsigned row, unsigned col) const
  {
    if (row == 1 && col == 1)
      return (COLOR)this->centers[(unsigned)f];

    // The colors are arranged Y, X, Z (see getCornerColors).
    if (f == FACE::UP)
    {
      if (row == 0)
      {
        if (col == 0)
          return this->getCornerColors(CORNER::ULB)[0];
        else if (col == 1)
          return this->getEdgeColors(EDGE::UB)[0];
        else
          return this->getCornerColors(CORNER::URB)[0];
      }
      else if (row == 1)
      {
        if (col == 0)
          return this->getEdgeColors(EDGE::UL)[0];
        else
          return this->getEdgeColors(EDGE::UR)[0];
      }
      else
      {
        if (col == 0)
          return this->getCornerColors(CORNER::ULF)[0];
        else if (col == 1)
          return this->getEdgeColors(EDGE::UF)[0];
        else
          return this->getCornerColors(CORNER::URF)[0];
      }
    }
    else if (f == FACE::LEFT)
    {
      if (row == 0)
      {
        if (col == 0)
          return this->getCornerColors(CORNER::ULB)[1];
        else if (col == 1)
          return this->getEdgeColors(EDGE::UL)[1];
        else
          return this->getCornerColors(CORNER::ULF)[1];
      }
      else if (row == 1)
      {
        if (col == 0)
          return this->getEdgeColors(EDGE::BL)[1];
        else
          return this->getEdgeColors(EDGE::FL)[1];
      }
      else
      {
        if (col == 0)
          return this->getCornerColors(CORNER::DLB)[1];
        else if (col == 1)
          return this->getEdgeColors(EDGE::DL)[1];
        else
          return this->getCornerColors(CORNER::DLF)[1];
      }
    }
    else if (f == FACE::FRONT)
    {
      if (row == 0)
      {
        if (col == 0)
          return this->getCornerColors(CORNER::ULF)[2];
        else if (col == 1)
          return this->getEdgeColors(EDGE::UF)[1];
        else
          return this->getCornerColors(CORNER::URF)[2];
      }
      else if (row == 1)
      {
        if (col == 0)
          return this->getEdgeColors(EDGE::FL)[0];
        else
          return this->getEdgeColors(EDGE::FR)[0];
      }
      else
      {
        if (col == 0)
          return this->getCornerColors(CORNER::DLF)[2];
        else if (col == 1)
          return this->getEdgeColors(EDGE::DF)[1];
        else
          return this->getCornerColors(CORNER::DRF)[2];
      }
    }
    else if (f == FACE::RIGHT)
    {
      if (row == 0)
      {
        if (col == 0)
          return this->getCornerColors(CORNER::URF)[1];
        else if (col == 1)
          return this->getEdgeColors(EDGE::UR)[1];
        else
          return this->getCornerColors(CORNER::URB)[1];
      }
      else if (row == 1)
      {
        if (col == 0)
          return this->getEdgeColors(EDGE::FR)[1];
        else
          return this->getEdgeColors(EDGE::BR)[1];
      }
      else
      {
        if (col == 0)
          return this->getCornerColors(CORNER::DRF)[1];
        else if (col == 1)
          return this->getEdgeColors(EDGE::DR)[1];
        else
          return this->getCornerColors(CORNER::DRB)[1];
      }
    }
    else if (f == FACE::BACK)
    {
      if (row == 0)
      {
        if (col == 0)
          return this->getCornerColors(CORNER::URB)[2];
        else if (col == 1)
          return this->getEdgeColors(EDGE::UB)[1];
        else
          return this->getCornerColors(CORNER::ULB)[2];
      }
      else if (row == 1)
      {
        if (col == 0)
          return this->getEdgeColors(EDGE::BR)[0];
        else
          return this->getEdgeColors(EDGE::BL)[0];
      }
      else
      {
        if (col == 0)
          return this->getCornerColors(CORNER::DRB)[2];
        else if (col == 1)
          return this->getEdgeColors(EDGE::DB)[1];
        else
          return this->getCornerColors(CORNER::DLB)[2];
      }
    }
    else // if (f == FACE::DOWN)
    {
      if (row == 0)
      {
        if (col == 0)
          return this->getCornerColors(CORNER::DLF)[0];
        else if (col == 1)
          return this->getEdgeColors(EDGE::DF)[0];
        else
          return this->getCornerColors(CORNER::DRF)[0];
      }
      else if (row == 1)
      {
        if (col == 0)
          return this->getEdgeColors(EDGE::DL)[0];
        else
          return this->getEdgeColors(EDGE::DR)[0];
      }
      else
      {
        if (col == 0)
          return this->getCornerColors(CORNER::DLB)[0];
        else if (col == 1)
          return this->getEdgeColors(EDGE::DB)[0];
        else
          return this->getCornerColors(CORNER::DRB)[0];
      }
    }
  }

  /**
   * Get the cubie index of an edge cubie.
   */
  uint8_t RubiksCubeIndexModel::getEdgeIndex(EDGE ind) const
  {
    return this->edges[(unsigned)ind].index;
  }

  /**
   * Get the orientation of an edge cubie.
   */
  uint8_t RubiksCubeIndexModel::getEdgeOrientation(EDGE ind) const
  {
    return this->edges[(unsigned)ind].orientation;
  }

  /**
   * Get the cubie index of a corner cubie.
   */
  uint8_t RubiksCubeIndexModel::getCornerIndex(CORNER ind) const
  {
    return this->corners[(unsigned)ind].index;
  }

  /**
   * Get the orientation of a corner cubie.
   */
  uint8_t RubiksCubeIndexModel::getCornerOrientation(CORNER ind) const
  {
    return this->corners[(unsigned)ind].orientation;
  }

  /**
   * Check if the cube is in a solved state.
   */
  bool RubiksCubeIndexModel::isSolved() const
  {
    for (unsigned i = 0; i < this->corners.size(); ++i)
    {
      if (this->corners[i].index != i || this->corners[i].orientation != 0)
        return false;
    }

    for (unsigned i = 0; i < this->edges.size(); ++i)
    {
      if (this->edges[i].index != i || this->edges[i].orientation != 0)
        return false;
    }

    return true;
  }

  /**
   * Helper to update the orientation of corners on an L or R turn.
   */
  inline void RubiksCubeIndexModel::updateCornerOrientationX(CORNER ind)
  {
    Cubie& corner = this->corners[(unsigned)ind];

    // The new orientation differs based on its distance from home.  E.g.
    // moving corner 0 (RBY) left moves it from ULB (0) to ULF (3).  That's an
    // odd distance (0+3), so the orientation is 1 (Y on top).  Moving corner 0
    // (RBY) left prime from ULF (3) to ULB (0) is even (0+0), so the
    // orientation is 2.
    bool evenDist = ((uint8_t)ind + corner.index) % 2 == 0;

    if (corner.orientation == 0)
      corner.orientation = evenDist ? 2 : 1;
    else if (corner.orientation == 1)
      corner.orientation = evenDist ? 0 : 2;
    else // if (corner.orientation == 2)
      corner.orientation = evenDist ? 1 : 0;
  }

  /**
   * Helper to update the orientation of corners on an F or B turn.
   */
  inline void RubiksCubeIndexModel::updateCornerOrientationZ(CORNER ind)
  {
    Cubie& corner = this->corners[(unsigned)ind];

    // Moving corner 3 (RBW) front moves it from ULF (3) to URF (2).  That's an
    // odd distance (3+2), so the orientation is 2 (B on top).  Moving corner 3
    // (RBW) front prime from URF (2) to ULF (3) is even (3+3), so the
    // orientation is 1.
    bool evenDist = ((uint8_t)ind + corner.index) % 2 == 0;

    if (corner.orientation == 0)
      corner.orientation = evenDist ? 1 : 2;
    else if (corner.orientation == 1)
      corner.orientation = evenDist ? 2 : 0;
    else // if (corner.orientation == 2)
      corner.orientation = evenDist ? 0 : 1;
  }

  /**
   * Helper to update the orientation of edges on an F or B turn.  Moving F or
   * B toggles the orientation of each edge.
   */
  inline void RubiksCubeIndexModel::updateEdgeOrientationZ(EDGE ind)
  {
    this->edges[(unsigned)ind].orientation ^= 1;
  }

  /**
   * Up.
   */
  RubiksCube& RubiksCubeIndexModel::u()
  {
    Cubie hold                           = this->corners[(unsigned)CORNER::ULF];
    this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::URF];
    this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::URB];
    this->corners[(unsigned)CORNER::URB] = this->corners[(unsigned)CORNER::ULB];
    this->corners[(unsigned)CORNER::ULB] = hold;

    hold                                 = this->edges[(unsigned)EDGE::UL];
    this->edges[(unsigned)EDGE::UL]      = this->edges[(unsigned)EDGE::UF];
    this->edges[(unsigned)EDGE::UF]      = this->edges[(unsigned)EDGE::UR];
    this->edges[(unsigned)EDGE::UR]      = this->edges[(unsigned)EDGE::UB];
    this->edges[(unsigned)EDGE::UB]      = hold;

    return *this;
  }

  /**
   * Up prime.
   */
  RubiksCube& RubiksCubeIndexModel::uPrime()
  {
    Cubie hold                           = this->corners[(unsigned)CORNER::ULB];
    this->corners[(unsigned)CORNER::ULB] = this->corners[(unsigned)CORNER::URB];
    this->corners[(unsigned)CORNER::URB] = this->corners[(unsigned)CORNER::URF];
    this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::ULF];
    this->corners[(unsigned)CORNER::ULF] = hold;

    hold                                 = this->edges[(unsigned)EDGE::UB];
    this->edges[(unsigned)EDGE::UB]      = this->edges[(unsigned)EDGE::UR];
    this->edges[(unsigned)EDGE::UR]      = this->edges[(unsigned)EDGE::UF];
    this->edges[(unsigned)EDGE::UF]      = this->edges[(unsigned)EDGE::UL];
    this->edges[(unsigned)EDGE::UL]      = hold;

    return *this;
  }

  /**
   * Up 2.
   */
  RubiksCube& RubiksCubeIndexModel::u2()
  {
    swap(this->corners[(unsigned)CORNER::ULB], this->corners[(unsigned)CORNER::URF]);
    swap(this->corners[(unsigned)CORNER::URB], this->corners[(unsigned)CORNER::ULF]);

    swap(this->edges[(unsigned)EDGE::UB],      this->edges[(unsigned)EDGE::UF]);
    swap(this->edges[(unsigned)EDGE::UR],      this->edges[(unsigned)EDGE::UL]);

    return *this;
  }

  /**
   * Left.
   */
  RubiksCube& RubiksCubeIndexModel::l()
  {
    Cubie hold                           = this->corners[(unsigned)CORNER::DLB];
    this->corners[(unsigned)CORNER::DLB] = this->corners[(unsigned)CORNER::DLF];
    this->corners[(unsigned)CORNER::DLF] = this->corners[(unsigned)CORNER::ULF];
    this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::ULB];
    this->corners[(unsigned)CORNER::ULB] = hold;

    hold                                 = this->edges[(unsigned)EDGE::BL];
    this->edges[(unsigned)EDGE::BL]      = this->edges[(unsigned)EDGE::DL];
    this->edges[(unsigned)EDGE::DL]      = this->edges[(unsigned)EDGE::FL];
    this->edges[(unsigned)EDGE::FL]      = this->edges[(unsigned)EDGE::UL];
    this->edges[(unsigned)EDGE::UL]      = hold;

    this->updateCornerOrientationX(CORNER::DLB);
    this->updateCornerOrientationX(CORNER::DLF);
    this->updateCornerOrientationX(CORNER::ULF);
    this->updateCornerOrientationX(CORNER::ULB);

    return *this;
  }

  /**
   * Left prime.
   */
  RubiksCube& RubiksCubeIndexModel::lPrime()
  {
    Cubie hold                           = this->corners[(unsigned)CORNER::DLB];
    this->corners[(unsigned)CORNER::DLB] = this->corners[(unsigned)CORNER::ULB];
    this->corners[(unsigned)CORNER::ULB] = this->corners[(unsigned)CORNER::ULF];
    this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::DLF];
    this->corners[(unsigned)CORNER::DLF] = hold;

    hold                                 = this->edges[(unsigned)EDGE::BL];
    this->edges[(unsigned)EDGE::BL]      = this->edges[(unsigned)EDGE::UL];
    this->edges[(unsigned)EDGE::UL]      = this->edges[(unsigned)EDGE::FL];
    this->edges[(unsigned)EDGE::FL]      = this->edges[(unsigned)EDGE::DL];
    this->edges[(unsigned)EDGE::DL]      = hold;

    this->updateCornerOrientationX(CORNER::DLB);
    this->updateCornerOrientationX(CORNER::DLF);
    this->updateCornerOrientationX(CORNER::ULF);
    this->updateCornerOrientationX(CORNER::ULB);

    return *this;
  }

  /**
   * Left 2.
   */
  RubiksCube& RubiksCubeIndexModel::l2()
  {
    swap(this->corners[(unsigned)CORNER::DLB], this->corners[(unsigned)CORNER::ULF]);
    swap(this->corners[(unsigned)CORNER::ULB], this->corners[(unsigned)CORNER::DLF]);

    swap(this->edges[(unsigned)EDGE::BL],      this->edges[(unsigned)EDGE::FL]);
    swap(this->edges[(unsigned)EDGE::UL],      this->edges[(unsigned)EDGE::DL]);

    return *this;
  }

  /**
   * Front.
   */
  RubiksCube& RubiksCubeIndexModel::f()
  {
    Cubie hold                           = this->corners[(unsigned)CORNER::ULF];
    this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::DLF];
    this->corners[(unsigned)CORNER::DLF] = this->corners[(unsigned)CORNER::DRF];
    this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::URF];
    this->corners[(unsigned)CORNER::URF] = hold;

    hold                                 = this->edges[(unsigned)EDGE::UF];
    this->edges[(unsigned)EDGE::UF]      = this->edges[(unsigned)EDGE::FL];
    this->edges[(unsigned)EDGE::FL]      = this->edges[(unsigned)EDGE::DF];
    this->edges[(unsigned)EDGE::DF]      = this->edges[(unsigned)EDGE::FR];
    this->edges[(unsigned)EDGE::FR]      = hold;

    this->updateCornerOrientationZ(CORNER::ULF);
    this->updateCornerOrientationZ(CORNER::URF);
    this->updateCornerOrientationZ(CORNER::DRF);
    this->updateCornerOrientationZ(CORNER::DLF);

    this->updateEdgeOrientationZ(EDGE::UF);
    this->updateEdgeOrientationZ(EDGE::FL);
    this->updateEdgeOrientationZ(EDGE::DF);
    this->updateEdgeOrientationZ(EDGE::FR);

    return *this;
  }

  /**
   * Front prime.
   */
  RubiksCube& RubiksCubeIndexModel::fPrime()
  {
    Cubie hold                           = this->corners[(unsigned)CORNER::ULF];
    this->corners[(unsigned)CORNER::ULF] = this->corners[(unsigned)CORNER::URF];
    this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::DRF];
    this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::DLF];
    this->corners[(unsigned)CORNER::DLF] = hold;

    hold                                 = this->edges[(unsigned)EDGE::UF];
    this->edges[(unsigned)EDGE::UF]      = this->edges[(unsigned)EDGE::FR];
    this->edges[(unsigned)EDGE::FR]      = this->edges[(unsigned)EDGE::DF];
    this->edges[(unsigned)EDGE::DF]      = this->edges[(unsigned)EDGE::FL];
    this->edges[(unsigned)EDGE::FL]      = hold;

    this->updateCornerOrientationZ(CORNER::ULF);
    this->updateCornerOrientationZ(CORNER::URF);
    this->updateCornerOrientationZ(CORNER::DRF);
    this->updateCornerOrientationZ(CORNER::DLF);

    this->updateEdgeOrientationZ(EDGE::UF);
    this->updateEdgeOrientationZ(EDGE::FL);
    this->updateEdgeOrientationZ(EDGE::DF);
    this->updateEdgeOrientationZ(EDGE::FR);

    return *this;
  }

  /**
   * Front 2.
   */
  RubiksCube& RubiksCubeIndexModel::f2()
  {
    swap(this->corners[(unsigned)CORNER::ULF], this->corners[(unsigned)CORNER::DRF]);
    swap(this->corners[(unsigned)CORNER::URF], this->corners[(unsigned)CORNER::DLF]);

    swap(this->edges[(unsigned)EDGE::UF],      this->edges[(unsigned)EDGE::DF]);
    swap(this->edges[(unsigned)EDGE::FL],      this->edges[(unsigned)EDGE::FR]);

    return *this;
  }

  /**
   * Right.
   */
  RubiksCube& RubiksCubeIndexModel::r()
  {
    Cubie hold                           = this->corners[(unsigned)CORNER::DRB];
    this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::URB];
    this->corners[(unsigned)CORNER::URB] = this->corners[(unsigned)CORNER::URF];
    this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::DRF];
    this->corners[(unsigned)CORNER::DRF] = hold;

    hold                                 = this->edges[(unsigned)EDGE::BR];
    this->edges[(unsigned)EDGE::BR]      = this->edges[(unsigned)EDGE::UR];
    this->edges[(unsigned)EDGE::UR]      = this->edges[(unsigned)EDGE::FR];
    this->edges[(unsigned)EDGE::FR]      = this->edges[(unsigned)EDGE::DR];
    this->edges[(unsigned)EDGE::DR]      = hold;

    this->updateCornerOrientationX(CORNER::DRB);
    this->updateCornerOrientationX(CORNER::DRF);
    this->updateCornerOrientationX(CORNER::URF);
    this->updateCornerOrientationX(CORNER::URB);

    return *this;
  }

  /**
   * Right prime.
   */
  RubiksCube& RubiksCubeIndexModel::rPrime()
  {
    Cubie hold                           = this->corners[(unsigned)CORNER::DRB];
    this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::DRF];
    this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::URF];
    this->corners[(unsigned)CORNER::URF] = this->corners[(unsigned)CORNER::URB];
    this->corners[(unsigned)CORNER::URB] = hold;

    hold                                 = this->edges[(unsigned)EDGE::BR];
    this->edges[(unsigned)EDGE::BR]      = this->edges[(unsigned)EDGE::DR];
    this->edges[(unsigned)EDGE::DR]      = this->edges[(unsigned)EDGE::FR];
    this->edges[(unsigned)EDGE::FR]      = this->edges[(unsigned)EDGE::UR];
    this->edges[(unsigned)EDGE::UR]      = hold;

    this->updateCornerOrientationX(CORNER::DRB);
    this->updateCornerOrientationX(CORNER::DRF);
    this->updateCornerOrientationX(CORNER::URF);
    this->updateCornerOrientationX(CORNER::URB);

    return *this;
  }

  /**
   * Right 2.
   */
  RubiksCube& RubiksCubeIndexModel::r2()
  {
    swap(this->corners[(unsigned)CORNER::DRB], this->corners[(unsigned)CORNER::URF]);
    swap(this->corners[(unsigned)CORNER::URB], this->corners[(unsigned)CORNER::DRF]);

    swap(this->edges[(unsigned)EDGE::BR],      this->edges[(unsigned)EDGE::FR]);
    swap(this->edges[(unsigned)EDGE::UR],      this->edges[(unsigned)EDGE::DR]);

    return *this;
  }

  /**
   * Back.
   */
  RubiksCube& RubiksCubeIndexModel::b()
  {
    Cubie hold                           = this->corners[(unsigned)CORNER::ULB];
    this->corners[(unsigned)CORNER::ULB] = this->corners[(unsigned)CORNER::URB];
    this->corners[(unsigned)CORNER::URB] = this->corners[(unsigned)CORNER::DRB];
    this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::DLB];
    this->corners[(unsigned)CORNER::DLB] = hold;

    hold                                 = this->edges[(unsigned)EDGE::UB];
    this->edges[(unsigned)EDGE::UB]      = this->edges[(unsigned)EDGE::BR];
    this->edges[(unsigned)EDGE::BR]      = this->edges[(unsigned)EDGE::DB];
    this->edges[(unsigned)EDGE::DB]      = this->edges[(unsigned)EDGE::BL];
    this->edges[(unsigned)EDGE::BL]      = hold;

    this->updateCornerOrientationZ(CORNER::ULB);
    this->updateCornerOrientationZ(CORNER::URB);
    this->updateCornerOrientationZ(CORNER::DRB);
    this->updateCornerOrientationZ(CORNER::DLB);

    this->updateEdgeOrientationZ(EDGE::UB);
    this->updateEdgeOrientationZ(EDGE::BL);
    this->updateEdgeOrientationZ(EDGE::DB);
    this->updateEdgeOrientationZ(EDGE::BR);

    return *this;
  }

  /**
   * Back prime.
   */
  RubiksCube& RubiksCubeIndexModel::bPrime()
  {
    Cubie hold                           = this->corners[(unsigned)CORNER::ULB];
    this->corners[(unsigned)CORNER::ULB] = this->corners[(unsigned)CORNER::DLB];
    this->corners[(unsigned)CORNER::DLB] = this->corners[(unsigned)CORNER::DRB];
    this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::URB];
    this->corners[(unsigned)CORNER::URB] = hold;

    hold                                 = this->edges[(unsigned)EDGE::UB];
    this->edges[(unsigned)EDGE::UB]      = this->edges[(unsigned)EDGE::BL];
    this->edges[(unsigned)EDGE::BL]      = this->edges[(unsigned)EDGE::DB];
    this->edges[(unsigned)EDGE::DB]      = this->edges[(unsigned)EDGE::BR];
    this->edges[(unsigned)EDGE::BR]      = hold;

    this->updateCornerOrientationZ(CORNER::ULB);
    this->updateCornerOrientationZ(CORNER::URB);
    this->updateCornerOrientationZ(CORNER::DRB);
    this->updateCornerOrientationZ(CORNER::DLB);

    this->updateEdgeOrientationZ(EDGE::UB);
    this->updateEdgeOrientationZ(EDGE::BL);
    this->updateEdgeOrientationZ(EDGE::DB);
    this->updateEdgeOrientationZ(EDGE::BR);

    return *this;
  }

  /**
   * Back 2.
   */
  RubiksCube& RubiksCubeIndexModel::b2()
  {
    swap(this->corners[(unsigned)CORNER::ULB], this->corners[(unsigned)CORNER::DRB]);
    swap(this->corners[(unsigned)CORNER::URB], this->corners[(unsigned)CORNER::DLB]);

    swap(this->edges[(unsigned)EDGE::UB],      this->edges[(unsigned)EDGE::DB]);
    swap(this->edges[(unsigned)EDGE::BL],      this->edges[(unsigned)EDGE::BR]);

    return *this;
  }

  /**
   * Down.
   */
  RubiksCube& RubiksCubeIndexModel::d()
  {
    Cubie hold                           = this->corners[(unsigned)CORNER::DLB];
    this->corners[(unsigned)CORNER::DLB] = this->corners[(unsigned)CORNER::DRB];
    this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::DRF];
    this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::DLF];
    this->corners[(unsigned)CORNER::DLF] = hold;

    hold                                 = this->edges[(unsigned)EDGE::DB];
    this->edges[(unsigned)EDGE::DB]      = this->edges[(unsigned)EDGE::DR];
    this->edges[(unsigned)EDGE::DR]      = this->edges[(unsigned)EDGE::DF];
    this->edges[(unsigned)EDGE::DF]      = this->edges[(unsigned)EDGE::DL];
    this->edges[(unsigned)EDGE::DL]      = hold;

    return *this;
  }

  /**
   * Down prime.
   */
  RubiksCube& RubiksCubeIndexModel::dPrime()
  {
    Cubie hold                           = this->corners[(unsigned)CORNER::DLF];
    this->corners[(unsigned)CORNER::DLF] = this->corners[(unsigned)CORNER::DRF];
    this->corners[(unsigned)CORNER::DRF] = this->corners[(unsigned)CORNER::DRB];
    this->corners[(unsigned)CORNER::DRB] = this->corners[(unsigned)CORNER::DLB];
    this->corners[(unsigned)CORNER::DLB] = hold;

    hold                                 = this->edges[(unsigned)EDGE::DL];
    this->edges[(unsigned)EDGE::DL]      = this->edges[(unsigned)EDGE::DF];
    this->edges[(unsigned)EDGE::DF]      = this->edges[(unsigned)EDGE::DR];
    this->edges[(unsigned)EDGE::DR]      = this->edges[(unsigned)EDGE::DB];
    this->edges[(unsigned)EDGE::DB]      = hold;

    return *this;
  }

  /**
   * Down 2.
   */
  RubiksCube& RubiksCubeIndexModel::d2()
  {
    swap(this->corners[(unsigned)CORNER::DLB], this->corners[(unsigned)CORNER::DRF]);
    swap(this->corners[(unsigned)CORNER::DRB], this->corners[(unsigned)CORNER::DLF]);

    swap(this->edges[(unsigned)EDGE::DB],      this->edges[(unsigned)EDGE::DF]);
    swap(this->edges[(unsigned)EDGE::DR],      this->edges[(unsigned)EDGE::DL]);

    return *this;
  }

  RubiksCube& RubiksCubeIndexModel::m()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::m not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::mPrime()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::mPrime not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::m2()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::m2 not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::e()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::e not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::ePrime()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::ePrime not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::e2()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::e2 not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::s()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::s not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::sPrime()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::sPrime not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::s2()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::s2 not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::y()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::y not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::y2()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::y2 not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::yPrime()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::yPrime not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::x()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::x not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::xPrime()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::xPrime not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::x2()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::x2 not implemented.");
  }


  RubiksCube& RubiksCubeIndexModel::z()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::z not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::zPrime()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::zPrime not implemented.");
  }

  RubiksCube& RubiksCubeIndexModel::z2()
  {
    throw RubiksCubeException("RubiksCubeIndexModel::z2 not implemented.");
  }
}

