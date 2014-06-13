#include "RubiksCubeModel.h"

namespace busybin
{
  /**
   * Initialize the cube, white on top, red in front.
   */
  RubiksCubeModel::RubiksCubeModel()
  {
    array<COLOR, 54>::iterator it  = this->cube.begin();
    array<COLOR, 54>::iterator end = next(it, 9);

    // Top.
    fill(it, end, COLOR::WHITE);

    // Left.
    it = end;
    advance(end, 9);
    fill(it, end, COLOR::GREEN);

    // Front.
    it = end;
    advance(end, 9);
    fill(it, end, COLOR::RED);

    // Right.
    it = end;
    advance(end, 9);
    fill(it, end, COLOR::BLUE);

    // Back.
    it = end;
    advance(end, 9);
    fill(it, end, COLOR::ORANGE);

    // Bottom.
    it = end;
    advance(end, 9);
    fill(it, end, COLOR::YELLOW);

    // Center cubies.
    this->centerCubies[(unsigned)FACE::UP]    = 4;
    this->centerCubies[(unsigned)FACE::LEFT]  = 13;
    this->centerCubies[(unsigned)FACE::FRONT] = 22;
    this->centerCubies[(unsigned)FACE::RIGHT] = 31;
    this->centerCubies[(unsigned)FACE::BACK]  = 40;
    this->centerCubies[(unsigned)FACE::DOWN]  = 49;

    // Edge cubies (order matters for the next_permuation calls).
    this->permuteEdge({{FACE::UP,    FACE::LEFT}},  {{3,  10}});
    this->permuteEdge({{FACE::UP,    FACE::FRONT}}, {{7,  19}});
    this->permuteEdge({{FACE::UP,    FACE::RIGHT}}, {{5,  28}});
    this->permuteEdge({{FACE::UP,    FACE::BACK}},  {{1,  37}});

    this->permuteEdge({{FACE::LEFT,  FACE::FRONT}}, {{14, 21}});
    this->permuteEdge({{FACE::FRONT, FACE::RIGHT}}, {{23, 30}});
    this->permuteEdge({{FACE::RIGHT, FACE::BACK}},  {{32, 39}});
    this->permuteEdge({{FACE::LEFT,  FACE::BACK}},  {{12, 41}});

    this->permuteEdge({{FACE::LEFT,  FACE::DOWN}},  {{16, 48}});
    this->permuteEdge({{FACE::FRONT, FACE::DOWN}},  {{25, 46}});
    this->permuteEdge({{FACE::RIGHT, FACE::DOWN}},  {{34, 50}});
    this->permuteEdge({{FACE::BACK,  FACE::DOWN}},  {{43, 52}});

    // Corner cubies.
    this->permuteCorner({{FACE::UP,    FACE::LEFT,  FACE::BACK}},  {{0,   9, 38}});
    this->permuteCorner({{FACE::UP,    FACE::LEFT,  FACE::FRONT}}, {{6,  11, 18}});
    this->permuteCorner({{FACE::UP,    FACE::FRONT, FACE::RIGHT}}, {{8,  20, 27}});
    this->permuteCorner({{FACE::UP,    FACE::RIGHT, FACE::BACK}},  {{2,  29, 36}});

    this->permuteCorner({{FACE::LEFT,  FACE::BACK,  FACE::DOWN}}, {{15, 44, 51}});
    this->permuteCorner({{FACE::LEFT,  FACE::FRONT, FACE::DOWN}}, {{17, 24, 45}});
    this->permuteCorner({{FACE::FRONT, FACE::RIGHT, FACE::DOWN}}, {{26, 33, 47}});
    this->permuteCorner({{FACE::RIGHT, FACE::BACK,  FACE::DOWN}}, {{35, 42, 53}});
  }

  /**
   * Insert all permutations of two faces/edges into the edgeCubies map.
   * @param faces The two faces.
   * @param indices The corresponding indices into the cube.
   */
  void RubiksCubeModel::permuteEdge(array<FACE, 2> faces, array<unsigned, 2> indices)
  {
    do
    {
      this->edgeCubies[faces] = indices;
    }
    while (next_permutation(faces.begin(), faces.end()) &&
      next_permutation(indices.begin(), indices.end()));
  }

  /**
   * Insert all permutations of two faces/edges into the cornerCubies map.
   * @param faces The three faces.
   * @param indices The corresponding indices into the cube.
   */
  void RubiksCubeModel::permuteCorner(array<FACE, 3> faces, array<unsigned, 3> indices)
  {
    do
    {
      this->cornerCubies[faces] = indices;
    }
    while (next_permutation(faces.begin(), faces.end()) &&
      next_permutation(indices.begin(), indices.end()));
  }

  /**
   * Get the color at index i.  The cube is laid out as follows.
   *
   *              W W W
   *              W W W
   *              W W W
   *
   *       G G G  R R R  B B B  O O O
   *       G G G  R R R  B B B  O O O
   *       G G G  R R R  B B B  O O O
   *
   *              Y Y Y
   *              Y Y Y
   *              Y Y Y
   *
   * Index wise:
   *
   *             0  1  2
   *             3  4  5
   *             6  7  8
   *
   *   9 10 11  18 19 20  27 28 29  36 37 38
   *  12 13 14  21 22 23  30 31 32  39 40 41
   *  15 16 17  24 25 26  33 34 35  42 43 44
   *
   *            45 46 47
   *            48 49 50
   *            51 52 53
   *
   * @param i The index.
   */
  RubiksCubeModel::COLOR RubiksCubeModel::get(unsigned i) const
  {
    if (i > 53)
      throw RubiksCubeException("Index out of bounds.");
    return this->cube.at(i);
  }

  /**
   * Get the color at FACE, row, col.  See get(i) overload for doc.
   * @param face The face of the cube.
   * @param row The 0-based row, unfolded as described in get(i).
   * @param col The 0-based col, unfulded as described in get(i).
   */
  RubiksCubeModel::COLOR RubiksCubeModel::get(RubiksCubeModel::FACE face,
    unsigned row, unsigned col) const
  {
    return this->get(9 * (unsigned)face + row * 3 + col);
  }

  /**
   * Get a center cubie by face.
   * @param f The face.
   */
  RubiksCubeModel::CenterCubie RubiksCubeModel::getCubie(FACE f) const
  {
    return this->cube[this->centerCubies[(unsigned)f]];
  }

  /**
   * Get an edge cubie by face.  e.g. TOP, LEFT edge.
   * @param f1 The first face.
   * @param f2 The second face.
   */
  RubiksCubeModel::EdgeCubie RubiksCubeModel::getCubie(FACE f1, FACE f2) const
  {
    array<unsigned, 2> ind = this->edgeCubies.at({{f1, f2}});

    return {{this->cube[ind[0]], this->cube[ind[1]]}};
  }

  /**
   * Get an edge cubie by face.  e.g. TOP, LEFT, BACK corner.
   * @param f1 The first face.
   * @param f2 The second face.
   * @param f3 The third face.
   */
  RubiksCubeModel::CornerCubie RubiksCubeModel::getCubie(FACE f1, FACE f2, FACE f3) const
  {
    array<unsigned, 3> ind = this->cornerCubies.at({{f1, f2, f3}});

    return {{this->cube[ind[0]], this->cube[ind[1]], this->cube[ind[2]]}};
  }

  /**
   * Check if the cube is solved.
   */
  bool RubiksCubeModel::isSolved() const
  {
    return
      this->isSolved(FACE::UP,    FACE::LEFT)  &&
      this->isSolved(FACE::UP,    FACE::FRONT) &&
      this->isSolved(FACE::UP,    FACE::RIGHT) &&
      this->isSolved(FACE::UP,    FACE::BACK)  &&
      this->isSolved(FACE::LEFT,  FACE::FRONT) &&
      this->isSolved(FACE::FRONT, FACE::RIGHT) &&
      this->isSolved(FACE::RIGHT, FACE::BACK)  &&
      this->isSolved(FACE::LEFT,  FACE::BACK)  &&
      this->isSolved(FACE::LEFT,  FACE::DOWN)  &&
      this->isSolved(FACE::FRONT, FACE::DOWN)  &&
      this->isSolved(FACE::RIGHT, FACE::DOWN)  &&
      this->isSolved(FACE::BACK,  FACE::DOWN)  &&
      this->isSolved(FACE::UP,    FACE::LEFT,  FACE::BACK)  &&
      this->isSolved(FACE::UP,    FACE::LEFT,  FACE::FRONT) &&
      this->isSolved(FACE::UP,    FACE::FRONT, FACE::RIGHT) &&
      this->isSolved(FACE::UP,    FACE::RIGHT, FACE::BACK)  &&
      this->isSolved(FACE::LEFT,  FACE::BACK,  FACE::DOWN)  &&
      this->isSolved(FACE::LEFT,  FACE::FRONT, FACE::DOWN)  &&
      this->isSolved(FACE::FRONT, FACE::RIGHT, FACE::DOWN)  &&
      this->isSolved(FACE::RIGHT, FACE::BACK,  FACE::DOWN);
  }

  /**
   * Check if a cubie is solved.
   * @param f1 The first face.
   * @param f2 The second face.
   */
  bool RubiksCubeModel::isSolved(FACE f1, FACE f2) const
  {
    EdgeCubie c = getCubie(f1, f2);

    return c[0] == getCubie(f1) && c[1] == getCubie(f2);
  }

  /**
   * Check if a cubie is solved.
   * @param f1 The first face.
   * @param f2 The second face.
   * @param f3 The third face.
   */
  bool RubiksCubeModel::isSolved(FACE f1, FACE f2, FACE f3) const
  {
    CornerCubie c = getCubie(f1, f2, f3);

    return c[0] == getCubie(f1) && c[1] == getCubie(f2) && c[2] == getCubie(f3);
  }

  /**
   * Move the up face clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::u()
  {
    array<COLOR, 54> copy = this->cube;

    for (int i = 0; i < 3; ++i)
    {
      // Up column.
      this->cube.at(9  + i) = copy.at(18 + i);
      this->cube.at(18 + i) = copy.at(27 + i);
      this->cube.at(27 + i) = copy.at(36 + i);
      this->cube.at(36 + i) = copy.at(9  + i);

      // Up face.
      this->cube.at(0 + i)     = copy.at(6 - i * 3);
      this->cube.at(0 + i * 3) = copy.at(6 + i);
      this->cube.at(2 + i * 3) = copy.at(0 + i);
      this->cube.at(6 + i)     = copy.at(8 - i * 3);
    }

    return *this;
  }

  /**
   * Move the up face counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::uPrime()
  {
    array<COLOR, 54> copy = this->cube;

    for (int i = 0; i < 3; ++i)
    {
      // Up column.
      this->cube.at(9  + i) = copy.at(36 + i);
      this->cube.at(18 + i) = copy.at(9  + i);
      this->cube.at(27 + i) = copy.at(18 + i);
      this->cube.at(36 + i) = copy.at(27 + i);

      // Up face.
      this->cube.at(0 + i)     = copy.at(2 + i * 3);
      this->cube.at(0 + i * 3) = copy.at(2 - i);
      this->cube.at(2 + i * 3) = copy.at(8 - i);
      this->cube.at(6 + i)     = copy.at(0 + i * 3);
    }

    return *this;
  }

  /**
   * Move the up face twice.
   */
  RubiksCubeModel& RubiksCubeModel::u2()
  {
    return this->u().u();
  }

  /**
   * Move the down face clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::d()
  {
    array<COLOR, 54> copy = this->cube;

    for (int i = 0; i < 3; ++i)
    {
      // Down column.
      this->cube.at(15 + i) = copy.at(42 + i);
      this->cube.at(24 + i) = copy.at(15 + i);
      this->cube.at(33 + i) = copy.at(24 + i);
      this->cube.at(42 + i) = copy.at(33 + i);

      // Down face.
      this->cube.at(45 + i)     = copy.at(51 - i * 3);
      this->cube.at(45 + i * 3) = copy.at(51 + i);
      this->cube.at(47 + i * 3) = copy.at(45 + i);
      this->cube.at(51 + i)     = copy.at(53 - i * 3);
    }

    return *this;
  }

  /**
   * Move the down face counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::dPrime()
  {
    array<COLOR, 54> copy = this->cube;

    for (int i = 0; i < 3; ++i)
    {
      // Down column.
      this->cube.at(15 + i) = copy.at(24 + i);
      this->cube.at(24 + i) = copy.at(33  + i);
      this->cube.at(33 + i) = copy.at(42 + i);
      this->cube.at(42 + i) = copy.at(15 + i);

      // Down face.
      this->cube.at(45 + i)     = copy.at(47 + i * 3);
      this->cube.at(45 + i * 3) = copy.at(47 - i);
      this->cube.at(47 + i * 3) = copy.at(53 - i);
      this->cube.at(51 + i)     = copy.at(45 + i * 3);
    }

    return *this;
  }

  /**
   * Move the down face twice.
   */
  RubiksCubeModel& RubiksCubeModel::d2()
  {
    return this->d().d();
  }

  /**
   * Move the left face clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::l()
  {
    array<COLOR, 54> copy = this->cube;

    for (int i = 0; i < 3; ++i)
    {
      // Left column.
      this->cube.at(0  + i * 3) = copy.at(44 - i * 3);
      this->cube.at(18 + i * 3) = copy.at(0  + i * 3);
      this->cube.at(45 + i * 3) = copy.at(18 + i * 3);
      this->cube.at(38 + i * 3) = copy.at(51 - i * 3);

      // Left face.
      this->cube.at(9  + i)     = copy.at(15 - i * 3);
      this->cube.at(9  + i * 3) = copy.at(15 + i);
      this->cube.at(11 + i * 3) = copy.at(9  + i);
      this->cube.at(15 + i)     = copy.at(17 - i * 3);
    }

    return *this;
  }

  /**
   * Move the left face counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::lPrime()
  {
    array<COLOR, 54> copy = this->cube;

    for (int i = 0; i < 3; ++i)
    {
      // Left column.
      this->cube.at(0  + i * 3) = copy.at(18 + i * 3);
      this->cube.at(18 + i * 3) = copy.at(45 + i * 3);
      this->cube.at(45 + i * 3) = copy.at(44 - i * 3);
      this->cube.at(38 + i * 3) = copy.at(6  - i * 3);

      // Left face.
      this->cube.at(9  + i)     = copy.at(11 + i * 3);
      this->cube.at(9  + i * 3) = copy.at(11 - i);
      this->cube.at(11 + i * 3) = copy.at(17 - i);
      this->cube.at(15 + i)     = copy.at(9  + i * 3);
    }

    return *this;
  }

  /**
   * Move the left face twice.
   */
  RubiksCubeModel& RubiksCubeModel::l2()
  {
    return this->l().l();
  }

  /**
   * Move the right face clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::r()
  {
    array<COLOR, 54> copy = this->cube;

    for (int i = 0; i < 3; ++i)
    {
      // Right column.
      this->cube.at(2  + i * 3) = copy.at(20 + i * 3);
      this->cube.at(20 + i * 3) = copy.at(47 + i * 3);
      this->cube.at(47 + i * 3) = copy.at(42 - i * 3);
      this->cube.at(36 + i * 3) = copy.at(8  - i * 3);

      // Right face.
      this->cube.at(27 + i)     = copy.at(33 - i * 3);
      this->cube.at(27 + i * 3) = copy.at(33 + i);
      this->cube.at(29 + i * 3) = copy.at(27 + i);
      this->cube.at(33 + i)     = copy.at(35 - i * 3);
    }

    return *this;
  }

  /**
   * Move the right face counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::rPrime()
  {
    array<COLOR, 54> copy = this->cube;

    for (int i = 0; i < 3; ++i)
    {
      // Right column.
      this->cube.at(2  + i * 3) = copy.at(42 - i * 3);
      this->cube.at(20 + i * 3) = copy.at(2  + i * 3);
      this->cube.at(47 + i * 3) = copy.at(20 + i * 3);
      this->cube.at(36 + i * 3) = copy.at(53 - i * 3);

      // Right face.
      this->cube.at(27 + i)     = copy.at(29 + i * 3);
      this->cube.at(27 + i * 3) = copy.at(29 - i);
      this->cube.at(29 + i * 3) = copy.at(35 - i);
      this->cube.at(33 + i)     = copy.at(27 + i * 3);
    }

    return *this;
  }

  /**
   * Move the right face twice.
   */
  RubiksCubeModel& RubiksCubeModel::r2()
  {
    return this->r().r();
  }

  /**
   * Move the front face clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::f()
  {
    array<COLOR, 54> copy = this->cube;

    for (int i = 0; i < 3; ++i)
    {
      // Front column.
      this->cube.at(6  + i)     = copy.at(17 - i * 3);
      this->cube.at(11 + i * 3) = copy.at(45 + i);
      this->cube.at(27 + i * 3) = copy.at(6  + i);
      this->cube.at(45 + i)     = copy.at(33 - i * 3);

      // Front face.
      this->cube.at(18 + i)     = copy.at(24 - i * 3);
      this->cube.at(18 + i * 3) = copy.at(24 + i);
      this->cube.at(20 + i * 3) = copy.at(18 + i);
      this->cube.at(24 + i)     = copy.at(26 - i * 3);
    }

    return *this;
  }

  /**
   * Move the front face counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::fPrime()
  {
    array<COLOR, 54> copy = this->cube;

    for (int i = 0; i < 3; ++i)
    {
      // Front column.
      this->cube.at(6  + i)     = copy.at(27 + i * 3);
      this->cube.at(11 + i * 3) = copy.at(8  - i);
      this->cube.at(27 + i * 3) = copy.at(47 - i);
      this->cube.at(45 + i)     = copy.at(11 + i * 3);

      // Front face.
      this->cube.at(18 + i)     = copy.at(20 + i * 3);
      this->cube.at(18 + i * 3) = copy.at(20 - i);
      this->cube.at(20 + i * 3) = copy.at(26 - i);
      this->cube.at(24 + i)     = copy.at(18 + i * 3);
    }

    return *this;
  }

  /**
   * Move the front face twice.
   */
  RubiksCubeModel& RubiksCubeModel::f2()
  {
    return this->f().f();
  }

  /**
   * Move the back face clockwise as if looking at the back.  From
   * the front this is counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::b()
  {
    array<COLOR, 54> copy = this->cube;

    for (int i = 0; i < 3; ++i)
    {
      // Back column.
      this->cube.at(0  + i)     = copy.at(29 + i * 3);
      this->cube.at(9  + i * 3) = copy.at(2  - i);
      this->cube.at(29 + i * 3) = copy.at(53 - i);
      this->cube.at(51 + i)     = copy.at(9  + i * 3);

      // Back face.
      this->cube.at(36 + i)     = copy.at(42 - i * 3);
      this->cube.at(36 + i * 3) = copy.at(42 + i);
      this->cube.at(38 + i * 3) = copy.at(36 + i);
      this->cube.at(42 + i)     = copy.at(44 - i * 3);
    }

    return *this;
  }

  /**
   * Move the back face counter clockwise as if looking at the back.  From
   * the front this is clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::bPrime()
  {
    array<COLOR, 54> copy = this->cube;

    for (int i = 0; i < 3; ++i)
    {
      // Back column.
      this->cube.at(0  + i)     = copy.at(15 - i * 3);
      this->cube.at(9  + i * 3) = copy.at(51 + i);
      this->cube.at(29 + i * 3) = copy.at(0  + i);
      this->cube.at(51 + i)     = copy.at(35 - i * 3);

      // Back face.
      this->cube.at(36 + i)     = copy.at(38 + i * 3);
      this->cube.at(36 + i * 3) = copy.at(38 - i);
      this->cube.at(38 + i * 3) = copy.at(44 - i);
      this->cube.at(42 + i)     = copy.at(36 + i * 3);
    }

    return *this;
  }

  /**
   * Move the back face twice.
   */
  RubiksCubeModel& RubiksCubeModel::b2()
  {
    return this->b().b();
  }

  /**
   * Move the M slice (between L and R, same way as L).
   */
  RubiksCubeModel& RubiksCubeModel::m()
  {
    array<COLOR, 54> copy = this->cube;

    this->cube.at(1)  = copy.at(43);
    this->cube.at(4)  = copy.at(40);
    this->cube.at(7)  = copy.at(37);
    this->cube.at(19) = copy.at(1);
    this->cube.at(22) = copy.at(4);
    this->cube.at(25) = copy.at(7);
    this->cube.at(46) = copy.at(19);
    this->cube.at(49) = copy.at(22);
    this->cube.at(52) = copy.at(25);
    this->cube.at(43) = copy.at(46);
    this->cube.at(40) = copy.at(49);
    this->cube.at(37) = copy.at(52);

    return *this;
  }

  /**
   * Move the M slice prime (between L and R, same way as L).
   */
  RubiksCubeModel& RubiksCubeModel::mPrime()
  {
    array<COLOR, 54> copy = this->cube;

    this->cube.at(43) = copy.at(1);
    this->cube.at(40) = copy.at(4);
    this->cube.at(37) = copy.at(7);
    this->cube.at(1)  = copy.at(19);
    this->cube.at(4)  = copy.at(22);
    this->cube.at(7)  = copy.at(25);
    this->cube.at(19) = copy.at(46);
    this->cube.at(22) = copy.at(49);
    this->cube.at(25) = copy.at(52);
    this->cube.at(46) = copy.at(43);
    this->cube.at(49) = copy.at(40);
    this->cube.at(52) = copy.at(37);

    return *this;
  }

  /**
   * Move m slice twice.
   */
  RubiksCubeModel& RubiksCubeModel::m2()
  {
    return this->m().m();
  }

  /**
   * Move the E slice (between U and D, same way as D).
   */
  RubiksCubeModel& RubiksCubeModel::e()
  {
    array<COLOR, 54> copy = this->cube;

    this->cube.at(12) = copy.at(39);
    this->cube.at(13) = copy.at(40);
    this->cube.at(14) = copy.at(41);
    this->cube.at(21) = copy.at(12);
    this->cube.at(22) = copy.at(13);
    this->cube.at(23) = copy.at(14);
    this->cube.at(30) = copy.at(21);
    this->cube.at(31) = copy.at(22);
    this->cube.at(32) = copy.at(23);
    this->cube.at(39) = copy.at(30);
    this->cube.at(40) = copy.at(31);
    this->cube.at(41) = copy.at(32);

    return *this;
  }

  /**
   * Move the E slice prime (between U and D, same way as D).
   */
  RubiksCubeModel& RubiksCubeModel::ePrime()
  {
    array<COLOR, 54> copy = this->cube;

    this->cube.at(39) = copy.at(12);
    this->cube.at(40) = copy.at(13);
    this->cube.at(41) = copy.at(14);
    this->cube.at(12) = copy.at(21);
    this->cube.at(13) = copy.at(22);
    this->cube.at(14) = copy.at(23);
    this->cube.at(21) = copy.at(30);
    this->cube.at(22) = copy.at(31);
    this->cube.at(23) = copy.at(32);
    this->cube.at(30) = copy.at(39);
    this->cube.at(31) = copy.at(40);
    this->cube.at(32) = copy.at(41);

    return *this;
  }

  /**
   * Move the E slice twice (between U and D, same way as D).
   */
  RubiksCubeModel& RubiksCubeModel::e2()
  {
    return this->e().e();
  }

  /**
   * Move the S slice (between F and B, same way as F).
   */
  RubiksCubeModel& RubiksCubeModel::s()
  {
    array<COLOR, 54> copy = this->cube;

    this->cube.at(3)  = copy.at(16);
    this->cube.at(4)  = copy.at(13);
    this->cube.at(5)  = copy.at(10);
    this->cube.at(28) = copy.at(3);
    this->cube.at(31) = copy.at(4);
    this->cube.at(34) = copy.at(5);
    this->cube.at(50) = copy.at(28);
    this->cube.at(49) = copy.at(31);
    this->cube.at(48) = copy.at(34);
    this->cube.at(16) = copy.at(50);
    this->cube.at(13) = copy.at(49);
    this->cube.at(10) = copy.at(48);

    return *this;
  }

  /**
   * Move the S slice prime (between F and B, same way as F).
   */
  RubiksCubeModel& RubiksCubeModel::sPrime()
  {
    array<COLOR, 54> copy = this->cube;

    this->cube.at(16) = copy.at(3);
    this->cube.at(13) = copy.at(4);
    this->cube.at(10) = copy.at(5);
    this->cube.at(3)  = copy.at(28);
    this->cube.at(4)  = copy.at(31);
    this->cube.at(5)  = copy.at(34);
    this->cube.at(28) = copy.at(50);
    this->cube.at(31) = copy.at(49);
    this->cube.at(34) = copy.at(48);
    this->cube.at(50) = copy.at(16);
    this->cube.at(49) = copy.at(13);
    this->cube.at(48) = copy.at(10);

    return *this;
  }

  /**
   * Move the S slice twice (between F and B, same way as F).
   */
  RubiksCubeModel& RubiksCubeModel::s2()
  {
    return this->s().s();
  }

  /**
   * Rotate the whole cube about the x axis (e.g. up) as if looking at the
   * R face.
   */
  RubiksCubeModel& RubiksCubeModel::x()
  {
    return this->lPrime().mPrime().r();
  }

  /**
   * Rotate the whole cube about the x axis (e.g. down) counter-clockwise 
   * as if looking at the R face.
   */
  RubiksCubeModel& RubiksCubeModel::xPrime()
  {
    return this->l().m().rPrime();
  }

  /**
   * Rotate the whole cube about the x axis twice.
   */
  RubiksCubeModel& RubiksCubeModel::x2()
  {
    return this->x().x();
  }

  /**
   * Rotate the whole cube about the y axis (e.g. left) as if looking at
   * the U face.
   */
  RubiksCubeModel& RubiksCubeModel::y()
  {
    return this->u().dPrime().ePrime();
  }

  /**
   * Rotate the whole cube about the y axis (e.g. right) counter-clockwise
   * as if looking at the U face.
   */
  RubiksCubeModel& RubiksCubeModel::yPrime()
  {
    return this->uPrime().d().e();
  }

  /**
   * Rotate the whole cube about the y axis twice.
   */
  RubiksCubeModel& RubiksCubeModel::y2()
  {
    return this->y().y();
  }

  /**
   * Rotate the whole cube about the z axis (e.g. sideways) as if looking at the
   * F face.
   */
  RubiksCubeModel& RubiksCubeModel::z()
  {
    return this->f().s().bPrime();
  }

  /**
   * Rotate the whole cube about the z axis (e.g. sideways) counter-clockwise 
   * as if looking at the F face.
   */
  RubiksCubeModel& RubiksCubeModel::zPrime()
  {
    return this->fPrime().sPrime().b();
  }

  /**
   * Rotate the whole cube about the z axis twice.
   */
  RubiksCubeModel& RubiksCubeModel::z2()
  {
    return this->z().z();
  }
}

