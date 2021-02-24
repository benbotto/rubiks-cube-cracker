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
    for (uint8_t i = 0; i < 8; ++i)
    {
      this->corners[i].index       = cube.getCornerIndex((RubiksCube::CORNER)i);
      this->corners[i].orientation = cube.getCornerOrientation((RubiksCube::CORNER)i);
    }

    // Edges.
    for (uint8_t i = 0; i < 12; ++i)
    {
      this->edges[i].index       = cube.getEdgeIndex((RubiksCube::EDGE)i);
      this->edges[i].orientation = cube.getEdgeOrientation((RubiksCube::EDGE)i);
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
   * Get the edge colors at an index.
   */
  array<RubiksCubeIndexModel::COLOR, 2> RubiksCubeIndexModel::getEdgeColors(
    RubiksCube::EDGE ind) const
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
    RubiksCube::CORNER ind) const
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
   * Helper to update the orientation of corners on 90-degree CW twist.
   * @param ind The corner index to update.
   * @param amount The amount to update the orientation by: 1, or 2.
   */
  inline void RubiksCubeIndexModel::updateCornerOrientation(
    CORNER ind, uint8_t amount)
  {
    Cubie& corner = this->corners[(unsigned)ind];

    // For 90-degree twists that change the orientation of corners, half of the
    // corners change orientation by 1 (0->1, 1->2, 2->0) and the other half
    // change by 2 (0->2, 1->0, 2->1 [mod 3]).
    // Orientation 0: Red or orange on top or bottom.
    // Orientation 1: Red or orange is twisted clockwise from its nearest up or
    // down face.
    // Orientation 2: Red or orange is twisted counterclockwise from its
    // nearest up or down face.
    corner.orientation += amount;

    // % 3, but a bit faster.
    if (corner.orientation == 3)
      corner.orientation = 0;
    else if (corner.orientation == 4)
      corner.orientation = 1;
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

    this->updateCornerOrientation(CORNER::DLB, 1);
    this->updateCornerOrientation(CORNER::DLF, 2);
    this->updateCornerOrientation(CORNER::ULF, 1);
    this->updateCornerOrientation(CORNER::ULB, 2);

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

    this->updateCornerOrientation(CORNER::DLB, 1);
    this->updateCornerOrientation(CORNER::DLF, 2);
    this->updateCornerOrientation(CORNER::ULF, 1);
    this->updateCornerOrientation(CORNER::ULB, 2);

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

    this->updateCornerOrientation(CORNER::ULF, 2);
    this->updateCornerOrientation(CORNER::URF, 1);
    this->updateCornerOrientation(CORNER::DRF, 2);
    this->updateCornerOrientation(CORNER::DLF, 1);

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

    this->updateCornerOrientation(CORNER::ULF, 2);
    this->updateCornerOrientation(CORNER::URF, 1);
    this->updateCornerOrientation(CORNER::DRF, 2);
    this->updateCornerOrientation(CORNER::DLF, 1);

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

    this->updateCornerOrientation(CORNER::DRB, 2);
    this->updateCornerOrientation(CORNER::DRF, 1);
    this->updateCornerOrientation(CORNER::URF, 2);
    this->updateCornerOrientation(CORNER::URB, 1);

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

    this->updateCornerOrientation(CORNER::DRB, 2);
    this->updateCornerOrientation(CORNER::DRF, 1);
    this->updateCornerOrientation(CORNER::URF, 2);
    this->updateCornerOrientation(CORNER::URB, 1);

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

    this->updateCornerOrientation(CORNER::ULB, 1);
    this->updateCornerOrientation(CORNER::URB, 2);
    this->updateCornerOrientation(CORNER::DRB, 1);
    this->updateCornerOrientation(CORNER::DLB, 2);

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

    this->updateCornerOrientation(CORNER::ULB, 1);
    this->updateCornerOrientation(CORNER::URB, 2);
    this->updateCornerOrientation(CORNER::DRB, 1);
    this->updateCornerOrientation(CORNER::DLB, 2);

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

