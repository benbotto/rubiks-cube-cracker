#include "RubiksCubeModel.h"

namespace busybin
{
  /**
   * Initialize the cube, white on top, red in front.
   */
  RubiksCubeModel::RubiksCubeModel()
  {
    array<COLOR, 48>::iterator it  = this->cube.begin();
    array<COLOR, 48>::iterator end = next(it, 8);

    // Top.
    fill(it, end, COLOR::WHITE);

    // Left.
    it = end;
    advance(end, 8);
    fill(it, end, COLOR::GREEN);

    // Front.
    it = end;
    advance(end, 8);
    fill(it, end, COLOR::RED);

    // Right.
    it = end;
    advance(end, 8);
    fill(it, end, COLOR::BLUE);

    // Back.
    it = end;
    advance(end, 8);
    fill(it, end, COLOR::ORANGE);

    // Bottom.
    it = end;
    advance(end, 8);
    fill(it, end, COLOR::YELLOW);

    // The center cubes are stored separately.  This allows for very fast
    // face rotations.  Additionally this allows each face to fit in
    // 64 bits, which can speed up solution checks.
    for (int i = 0; i < 6; ++i)
      this->centers[i] = (COLOR)i;
  }

  /**
   * Copy from another cube.
   */
  RubiksCubeModel::RubiksCubeModel(const RubiksCubeModel& cube)
  {
    memcpy(reinterpret_cast<void*>(&this->cube[0]),
      reinterpret_cast<const void*>(&cube.cube[0]), 48);
    memcpy(reinterpret_cast<void*>(&this->centers[0]),
      reinterpret_cast<const void*>(&cube.centers[0]), 6);
  }

  /**
   * Same as above, but using the equals operator.
   */
  RubiksCubeModel& RubiksCubeModel::operator=(const RubiksCubeModel rhs)
  {
    memcpy(reinterpret_cast<void*>(&this->cube[0]),
      reinterpret_cast<const void*>(&rhs.cube[0]), 48);
    memcpy(reinterpret_cast<void*>(&this->centers[0]),
      reinterpret_cast<const void*>(&rhs.centers[0]), 6);

    return *this;
  }

  /**
   * Roll an array right 2 places, and wrap around.  This is a 90-degree
   * rotation of a face.
   *
   * Input:  0 1 2 3 4 5 6 7 
   * Output: 6 7 0 1 2 3 4 5 
   *
   * @param f The face to roll.
   */
  inline void RubiksCubeModel::roll90(FACE f)
  {
    uint64_t face = *(uint64_t*)&this->cube[(unsigned)f * 8];
    asm volatile ("rolq $16, %[face]" : [face] "+r" (face) : );
    *(uint64_t*)&this->cube[(unsigned)f * 8] = face;
  }

  /**
   * Roll an array right 4 places, and wrap away.  This is a 180-degree
   * rotation of a face.
   *
   * Input:  0 1 2 3 4 5 6 7 
   * Output: 4 5 6 7 0 1 2 3 
   *
   * @param f The face to roll.
   */
  inline void RubiksCubeModel::roll180(FACE f)
  {
    uint64_t face = *(uint64_t*)&this->cube[(unsigned)f * 8];
    asm volatile ("rolq $32, %[face]" : [face] "+r" (face) : );
    *(uint64_t*)&this->cube[(unsigned)f * 8] = face;
  }

  /**
   * Roll an array right 6 places, and wrap away.  This is a 270-degree
   * rotation of a face.
   *
   * Input:  0 1 2 3 4 5 6 7 
   * Output: 2 3 4 5 6 7 0 1
   *
   * @param f The face to roll.
   */
  inline void RubiksCubeModel::roll270(FACE f)
  {
    uint64_t face = *(uint64_t*)&this->cube[(unsigned)f * 8];
    asm volatile ("rorq $16, %[face]" : [face] "+r" (face) : );
    *(uint64_t*)&this->cube[(unsigned)f * 8] = face;
  }

  /**
   * Rotate four sides 90 degrees.  Use roll to rotate the face.
   * @param s_i0 The first index, treated as a short.
   * @param s_i1 The second index, treated as a short.
   * @param s_i2 The third index, treated as a short.
   * @param s_i3 The fourth index, treated as a short.
   * @param c_i0 The first index, treated as a char.
   * @param c_i1 The second index, treated as a char.
   * @param c_i2 The third index, treated as a char.
   * @param c_i3 The fourth index, treated as a char.
   */
  inline void RubiksCubeModel::rotateSides90(unsigned s_i0, unsigned s_i1, unsigned s_i2, unsigned s_i3,
    unsigned c_i0, unsigned c_i1, unsigned c_i2, unsigned c_i3)
  {
    // The number of operations is reduced by moving two cubes at a time (e.g.
    // treating the cubes at index s_i0..s_i3 as 16-bit shorts).
    uint16_t hold_s_i0 = *((uint16_t*)&this->cube[s_i0]);

    *((uint16_t*)&this->cube[s_i0]) = *((uint16_t*)&this->cube[s_i1]);
    *((uint16_t*)&this->cube[s_i1]) = *((uint16_t*)&this->cube[s_i2]);
    *((uint16_t*)&this->cube[s_i2]) = *((uint16_t*)&this->cube[s_i3]);
    *((uint16_t*)&this->cube[s_i3]) = hold_s_i0;

    // The last four cubes need to be moved one at a time.
    COLOR hold_c_i0 = this->cube[c_i0];

    this->cube[c_i0] = this->cube[c_i1];
    this->cube[c_i1] = this->cube[c_i2];
    this->cube[c_i2] = this->cube[c_i3];
    this->cube[c_i3] = hold_c_i0;
  }

  /**
   * Rotate four sides 180 degrees.  Use roll to rotate the face.
   * @param s_i0 The first index, treated as a short.
   * @param s_i1 The second index, treated as a short.
   * @param s_i2 The third index, treated as a short.
   * @param s_i3 The fourth index, treated as a short.
   * @param c_i0 The first index, treated as a char.
   * @param c_i1 The second index, treated as a char.
   * @param c_i2 The third index, treated as a char.
   * @param c_i3 The fourth index, treated as a char.
   */
  inline void RubiksCubeModel::rotateSides180(
    unsigned s_i0, unsigned s_i1, unsigned s_i2, unsigned s_i3,
    unsigned c_i0, unsigned c_i1, unsigned c_i2, unsigned c_i3)
  {
    swap(*((uint16_t*)&this->cube[s_i0]), *((uint16_t*)&this->cube[s_i1]));
    swap(*((uint16_t*)&this->cube[s_i2]), *((uint16_t*)&this->cube[s_i3]));
    swap(this->cube[c_i0], this->cube[c_i1]);
    swap(this->cube[c_i2], this->cube[c_i3]);
  }

  /**
   * Rotate a slice 90 degrees.
   * @param c_fi0 Face index 0.
   * @param c_fi1 Face index 1.
   * @param c_fi2 Face index 2.
   * @param c_fi3 Face index 3.
   * @param c_fi4 Face index 4.
   * @param c_fi5 Face index 5.
   * @param c_fi6 Face index 6.
   * @param c_fi7 Face index 7.
   * @param c_ci0 Center index 0.
   * @param c_ci1 Center index 1.
   * @param c_ci2 Center index 2.
   * @param c_ci3 Center index 3.
   */
  inline void RubiksCubeModel::rotateSlice90(
    unsigned c_fi0, unsigned c_fi1, unsigned c_fi2, unsigned c_fi3,
    unsigned c_fi4, unsigned c_fi5, unsigned c_fi6, unsigned c_fi7,
    unsigned c_ci0, unsigned c_ci1, unsigned c_ci2, unsigned c_ci3)
  {
    COLOR hold_c_fi0  = this->cube[c_fi0];
    this->cube[c_fi0] = this->cube[c_fi1];
    this->cube[c_fi1] = this->cube[c_fi2];
    this->cube[c_fi2] = this->cube[c_fi3];
    this->cube[c_fi3] = hold_c_fi0;
    
    COLOR hold_c_fi4  = this->cube[c_fi4];
    this->cube[c_fi4] = this->cube[c_fi5];
    this->cube[c_fi5] = this->cube[c_fi6];
    this->cube[c_fi6] = this->cube[c_fi7];
    this->cube[c_fi7] = hold_c_fi4;

    COLOR hold_c_ci0     = this->centers[c_ci0];
    this->centers[c_ci0] = this->centers[c_ci1];
    this->centers[c_ci1] = this->centers[c_ci2];
    this->centers[c_ci2] = this->centers[c_ci3];
    this->centers[c_ci3] = hold_c_ci0;
  }

  /**
   * Rotate a slice 180 degrees.
   * @param c_fi0 Face index 0.
   * @param c_fi1 Face index 1.
   * @param c_fi2 Face index 2.
   * @param c_fi3 Face index 3.
   * @param c_fi4 Face index 4.
   * @param c_fi5 Face index 5.
   * @param c_fi6 Face index 6.
   * @param c_fi7 Face index 7.
   * @param c_ci0 Center index 0.
   * @param c_ci1 Center index 1.
   * @param c_ci2 Center index 2.
   * @param c_ci3 Center index 3.
   */
  inline void RubiksCubeModel::rotateSlice180(
    unsigned c_fi0, unsigned c_fi1, unsigned c_fi2, unsigned c_fi3,
    unsigned c_fi4, unsigned c_fi5, unsigned c_fi6, unsigned c_fi7,
    unsigned c_ci0, unsigned c_ci1, unsigned c_ci2, unsigned c_ci3)
  {
    swap(this->cube[c_fi0], this->cube[c_fi1]);
    swap(this->cube[c_fi2], this->cube[c_fi3]);
    swap(this->cube[c_fi4], this->cube[c_fi5]);
    swap(this->cube[c_fi6], this->cube[c_fi7]);

    swap(this->centers[c_ci0], this->centers[c_ci1]);
    swap(this->centers[c_ci2], this->centers[c_ci3]);
  }

  /**
   * Get the color at FACE, row, col.
   * @param f The face of the cube.
   * @param row The 0-based row, unfolded as described in the header.
   * @param col The 0-based col, unfolded as described in the header.
   */
  RubiksCube::COLOR RubiksCubeModel::getColor(
    RubiksCube::FACE f, unsigned row, unsigned col) const
  {
    if (row == 1 && col == 1)
      return (COLOR)this->centers[(unsigned)f];
    else
    {
      /* Row-column lookup.  A face stores stickers as follows.
       *  
       *  0 1 2
       *  7   3
       *  6 5 4
       *
       *  So, for example, row 2 col 1 is at index 5.
       *  row * 3 + col = 2 * 3 + 1 = 7.  lookup[7] == 5.
       */
      unsigned lookup[] = {0, 1, 2, 7, 0, 3, 6, 5, 4};
      unsigned index    = lookup[row * 3 + col];

      return (COLOR)this->cube[(unsigned)f * 8 + index];
    }
  }

  /**
   * Get the color at an index.
   * @param ind The index of the color.  See the diagram in the
   * RubiksCubeModel.h file.
   */
  RubiksCube::COLOR RubiksCubeModel::getColor(unsigned ind) const
  {
    return (COLOR)this->cube[ind];
  }

  /**
   * Get an entire face of the cube as a 64-bit int.
   * @param face The face to get.
   */
  uint64_t RubiksCubeModel::getFace(FACE face) const
  {
    return *(uint64_t*)&this->cube[(unsigned)face * 8];
  }

  /**
   * Check if the cube is in a solved state.  This is used by the solvers, and
   * the cube is expected to have red on top and white in the front.
   */
  bool RubiksCubeModel::isSolved() const
  {
    return
      this->getFace(FACE::FRONT) == 0x0000000000000000 &&
      this->getFace(FACE::RIGHT) == 0x0101010101010101 &&
      this->getFace(FACE::UP)    == 0x0202020202020202 &&
      this->getFace(FACE::LEFT)  == 0x0303030303030303 &&
      this->getFace(FACE::DOWN)  == 0x0404040404040404 &&
      this->getFace(FACE::BACK)  == 0x0505050505050505;
  }

  /**
   * Given three face colors, return a unique index for a corner cubie.  The
   * index will be [0..7].
   * @param corner An array of three colors, in any order.
   */
  uint8_t RubiksCubeModel::getCornerIndex(const corner_t& corner) const
  {
    // The colors range from 0 to 5, per RubiksCube.h.
    // Shifting 1 left by 0...5 gives 1, 2, 4, 8, 16, 32.
    // Adding these together gives a unique number for each corner cubie.
    // RBY = 4  + 8 + 32 = 44, index 0
    // RGY = 4  + 2 + 32 = 38, index 1
    // RGW = 4  + 1 + 2  = 7,  index 2
    // RBW = 4  + 8 + 1  = 13, index 3
    // OBW = 16 + 1 + 8  = 25, index 4
    // OBY = 16 + 8 + 32 = 56, index 5
    // OGY = 16 + 2 + 32 = 50, index 6
    // OGW = 16 + 2 + 1  = 19, index 7
    uint8_t sideSum =
      (1 << (uint8_t)corner[0]) +
      (1 << (uint8_t)corner[1]) +
      (1 << (uint8_t)corner[2]);

    switch (sideSum)
    {
      case 44:
        return 0;
      case 38:
        return 1;
      case 7:
        return 2;
      case 13:
        return 3;
      case 25:
        return 4;
      case 56:
        return 5;
      case 50:
        return 6;
      default: //case 19:
        return 7;
    }
  }

  /**
   * Given three face colors, return the orientation of the corner cubie, 0, 1,
   * or 2.  The up or down facet must be the first in the corner array.  The
   * cube must have red on top, white in front.
   * Orientation 0: Red or orange is on the top or bottom.
   * Orientation 1: White or yellow is on the top or bottom.
   * Orientation 2: Blue or green is on the top or bottom.
   * @param corner An array of three colors, with the up or down facet first.
   */
  uint8_t RubiksCubeModel::getCornerOrientation(const corner_t& corner) const
  {
    switch (corner[0])
    {
      case RubiksCube::COLOR::RED:
      case RubiksCube::COLOR::ORANGE:
        return 0;

      case RubiksCube::COLOR::WHITE:
      case RubiksCube::COLOR::YELLOW:
        return 1;

      default: // Blue or green.
        return 2;
    }
  }

  /**
   * Given two face colors, return a unique index for an edge cubie.  The index
   * will be [0..11].
   * @param edge An array of two colors, in any order.
   */
  uint8_t RubiksCubeModel::getEdgeIndex(const edge_t& edge) const
  {
    // The colors range from 0 to 5, per RubiksCube.h.
    // Shifting 1 left by 0...5 gives 1, 2, 4, 8, 16, 32.
    // Adding these together gives a unique number for each edge cubie.
    // RY = 4  + 32 = 36, index 0.
    // RG = 4  + 2  = 6,  index 1.
    // RW = 4  + 1  = 5,  index 2.
    // RB = 4  + 8  = 12, index 3.
    //
    // WG = 1  + 2  = 3,  index 4.
    // WB = 1  + 8  = 9,  index 5.
    // YB = 32 + 8  = 40, index 6.
    // YG = 32 + 2  = 34, index 7.
    //
    // OW = 16 + 1  = 17, index 8.
    // OB = 16 + 8  = 24, index 9.
    // OY = 16 + 32 = 48, index 10.
    // OG = 16 + 2  = 18, index 11.
    uint8_t sideSum =
      (1 << (uint8_t)edge[0]) +
      (1 << (uint8_t)edge[1]);

    switch (sideSum)
    {
      case 36:
        return 0;
      case 6:
        return 1;
      case 5:
        return 2;
      case 12:
        return 3;

      case 3:
        return 4;
      case 9:
        return 5;
      case 40:
        return 6;
      case 34:
        return 7;

      case 17:
        return 8;
      case 24:
        return 9;
      case 48:
        return 10;
      default: // 18
        return 11;
    }
  }

  /**
   * Given two face colors, return the orientation of the edge cubie, 0, or 1.
   * The up or down facet must be the first in the edge array for the top and
   * bottom layers, and the front or back facet must be the first edge in the
   * array for the middle layer..
   *
   * The cube is expected to be have red on top, white up front.
   *
   * Note that edges cannot be flipped (disoriented) without F or B turns, so
   * U, D, L, and R keep the edges oriented.
   *
   * Orientation 0: Good.
   * Orientation 1: Bad (disoriented).
   *
   * See: https://stackoverflow.com/questions/17305071/how-can-i-determine-optimally-if-an-edge-is-correctly-oriented-on-the-rubiks-cu
   * See: http://cube.crider.co.uk/zz.php?p=eoline#eo_detection
   *
   * @param edge An array of two colors.
   */
  uint8_t RubiksCubeModel::getEdgeOrientation(const edge_t& edge) const
  {
    // If the U or D sticker is the L or R color (blue or green), it's bad.
    if (edge[0] == RubiksCube::COLOR::BLUE ||
      edge[0] == RubiksCube::COLOR::GREEN)
    {
      return 1;
    }

    // If the U or D sticker is the F or B color (white or yellow), then check
    // the other edge.  If the other edge is the U or D color (red or orange),
    // it's bad.
    if (edge[0] == RubiksCube::COLOR::WHITE ||
      edge[0] == RubiksCube::COLOR::YELLOW)
    {
      if (edge[1] == RubiksCube::COLOR::RED ||
        edge[1] == RubiksCube::COLOR::ORANGE)
      {
        return 1;
      }
    }

    // Otherwise it's good.
    return 0;
  }

  /**
   * Compare two cubes (integer comparison of each side).
   */
  bool RubiksCubeModel::operator<(const RubiksCubeModel& rhs) const
  {
    for (uint8_t i = 0; i < 6; ++i)
      if (this->getFace((FACE)i) < rhs.getFace((FACE)i))
        return true;

    return false;
  }

  /**
   * Compare two cubes (integer comparison of each side).
   */
  bool RubiksCubeModel::operator==(const RubiksCubeModel& rhs) const
  {
    for (uint8_t i = 0; i < 6; ++i)
      if (this->getFace((FACE)i) != rhs.getFace((FACE)i))
        return false;

    return true;
  }

  /**
   * Move the up face clockwise.
   */
  RubiksCube& RubiksCubeModel::u()
  {
    // Rotate the stickers on the face.
    this->roll90(FACE::UP);

    // Update the sides.
    this->rotateSides90(8, 16, 24, 32, 10, 18, 26, 34);

    return *this;
  }

  /**
   * Move the up face counter clockwise.
   */
  RubiksCube& RubiksCubeModel::uPrime()
  {
    this->roll270(FACE::UP);
    this->rotateSides90(32, 24, 16, 8, 34, 26, 18, 10);
    return *this;
  }

  /**
   * Move the up face twice
   */
  RubiksCube& RubiksCubeModel::u2()
  {
    this->roll180(FACE::UP);
    this->rotateSides180(8, 24, 16, 32, 10, 26, 18, 34);
    return *this;
  }

  /**
   * Move the left face clockwise.
   */
  RubiksCube& RubiksCubeModel::l()
  {
    this->roll90(FACE::LEFT);
    this->rotateSides90(6, 34, 46, 22, 0, 36, 40, 16);
    return *this;
  }

  /**
   * Move the left face counter clockwise.
   */
  RubiksCube& RubiksCubeModel::lPrime()
  {
    this->roll270(FACE::LEFT);
    this->rotateSides90(22, 46, 34, 6, 16, 40, 36, 0);
    return *this;
  }

  /**
   * Move the left face twice.
   */
  RubiksCube& RubiksCubeModel::l2()
  {
    this->roll180(FACE::LEFT);
    this->rotateSides180(6, 46, 34, 22, 0, 40, 36, 16);
    return *this;
  }

  /**
   * Move the front face clockwise.
   */
  RubiksCube& RubiksCubeModel::f()
  {
    this->roll90(FACE::FRONT);
    this->rotateSides90(4, 10, 40, 30, 6, 12, 42, 24);
    return *this;
  }

  /**
   * Move the front face counter clockwise.
   */
  RubiksCube& RubiksCubeModel::fPrime()
  {
    this->roll270(FACE::FRONT);
    this->rotateSides90(30, 40, 10, 4, 24, 42, 12, 6);
    return *this;
  }

  /**
   * Move the front face twice.
   */
  RubiksCube& RubiksCubeModel::f2()
  {
    this->roll180(FACE::FRONT);
    this->rotateSides180(4, 40, 10, 30, 6, 42, 12, 24);
    return *this;
  }

  /**
   * Move the right face clockwise.
   */
  RubiksCube& RubiksCubeModel::r()
  {
    this->roll90(FACE::RIGHT);
    this->rotateSides90(2, 18, 42, 38, 4, 20, 44, 32);
    return *this;
  }

  /**
   * Move the right face counter clockwise.
   */
  RubiksCube& RubiksCubeModel::rPrime()
  {
    this->roll270(FACE::RIGHT);
    this->rotateSides90(38, 42, 18, 2, 32, 44, 20, 4);
    return *this;
  }

  /**
   * Move the right face twice.
   */
  RubiksCube& RubiksCubeModel::r2()
  {
    this->roll180(FACE::RIGHT);
    this->rotateSides180(2, 42, 18, 38, 4, 44, 20, 32);
    return *this;
  }

  /**
   * Move the back face clockwise.
   */
  RubiksCube& RubiksCubeModel::b()
  {
    this->roll90(FACE::BACK);
    this->rotateSides90(0, 26, 44, 14, 2, 28, 46, 8);
    return *this;
  }

  /**
   * Move the back face counter clockwise.
   */
  RubiksCube& RubiksCubeModel::bPrime()
  {
    this->roll270(FACE::BACK);
    this->rotateSides90(14, 44, 26, 0, 8, 46, 28, 2);
    return *this;
  }

  /**
   * Move the back face twice.
   */
  RubiksCube& RubiksCubeModel::b2()
  {
    this->roll180(FACE::BACK);
    this->rotateSides180(0, 44, 26, 14, 2, 46, 28, 8);
    return *this;
  }

  /**
   * Move the down face clockwise.
   */
  RubiksCube& RubiksCubeModel::d()
  {
    this->roll90(FACE::DOWN);
    this->rotateSides90(12, 36, 28, 20, 14, 38, 30, 22);
    return *this;
  }

  /**
   * Move the down face counter clockwise.
   */
  RubiksCube& RubiksCubeModel::dPrime()
  {
    this->roll270(FACE::DOWN);
    this->rotateSides90(20, 28, 36, 12, 22, 30, 38, 14);
    return *this;
  }

  /**
   * Move the down face twice.
   */
  RubiksCube& RubiksCubeModel::d2()
  {
    this->roll180(FACE::DOWN);
    this->rotateSides180(12, 28, 36, 20, 14, 30, 38, 22);
    return *this;
  }

  /**
   * Rotate the M slice clockwise (between R and L, same way as L).
   */
  RubiksCube& RubiksCubeModel::m()
  {
    this->rotateSlice90(1, 37, 41, 17, 5, 33, 45, 21, 0, 4, 5, 2);
    return *this;
  }

  /**
   * Rotate the M slice counter clockwise.
   */
  RubiksCube& RubiksCubeModel::mPrime()
  {
    this->rotateSlice90(17, 41, 37, 1, 21, 45, 33, 5, 2, 5, 4, 0);
    return *this;
  }

  /**
   * Rotate the M slice twice.
   */
  RubiksCube& RubiksCubeModel::m2()
  {
    this->rotateSlice180(1, 41, 37, 17, 5, 45, 33, 21, 0, 5, 4, 2);
    return *this;
  }

  /**
   * Rotate the E slice clockwise (between U and D, same way as D).
   */
  RubiksCube& RubiksCubeModel::e()
  {
    this->rotateSlice90(15, 39, 31, 23, 11, 35, 27, 19, 1, 4, 3, 2);
    return *this;
  }

  /**
   * Rotate the E slice counter clockwise.
   */
  RubiksCube& RubiksCubeModel::ePrime()
  {
    this->rotateSlice90(23, 31, 39, 15, 19, 27, 35, 11, 2, 3, 4, 1);
    return *this;
  }

  /**
   * Rotate the E slice twice.
   */
  RubiksCube& RubiksCubeModel::e2()
  {
    this->rotateSlice180(15, 31, 39, 23, 11, 27, 35, 19, 1, 3, 4, 2);
    return *this;
  }

  /**
   * Rotate the S slice clockwise (between B and F, same way as F).
   */
  RubiksCube& RubiksCubeModel::s()
  {
    this->rotateSlice90(3, 9, 47, 29, 7, 13, 43, 25, 0, 1, 5, 3);
    return *this;
  }

  /**
   * Rotate the S slice counter clockwise.
   */
  RubiksCube& RubiksCubeModel::sPrime()
  {
    this->rotateSlice90(29, 47, 9, 3, 25, 43, 13, 7, 3, 5, 1, 0);
    return *this;
  }

  /**
   * Rotate the S slice twice.
   */
  RubiksCube& RubiksCubeModel::s2()
  {
    this->rotateSlice180(3, 47, 9, 29, 7, 43, 13, 25, 0, 5, 1, 3);
    return *this;
  }

  /**
   * Rotate the whole cube about the x axis (e.g. up) as if looking at the
   * R face.
   */
  RubiksCube& RubiksCubeModel::x()
  {
    return this->lPrime().mPrime().r();
  }

  /**
   * Rotate the whole cube about the x axis (e.g. down) counter clockwise 
   * as if looking at the R face.
   */
  RubiksCube& RubiksCubeModel::xPrime()
  {
    return this->l().m().rPrime();
  }

  /**
   * Rotate the whole cube about the x axis twice.
   */
  RubiksCube& RubiksCubeModel::x2()
  {
    return this->x().x();
  }

  /**
   * Rotate the whole cube about the y axis (e.g. left) as if looking at
   * the U face.
   */
  RubiksCube& RubiksCubeModel::y()
  {
    return this->u().dPrime().ePrime();
  }

  /**
   * Rotate the whole cube about the y axis (e.g. right) counter clockwise
   * as if looking at the U face.
   */
  RubiksCube& RubiksCubeModel::yPrime()
  {
    return this->uPrime().d().e();
  }

  /**
   * Rotate the whole cube about the y axis twice.
   */
  RubiksCube& RubiksCubeModel::y2()
  {
    return this->y().y();
  }

  /**
   * Rotate the whole cube about the z axis (e.g. sideways) as if looking at the
   * F face.
   */
  RubiksCube& RubiksCubeModel::z()
  {
    return this->f().s().bPrime();
  }

  /**
   * Rotate the whole cube about the z axis (e.g. sideways) counter clockwise 
   * as if looking at the F face.
   */
  RubiksCube& RubiksCubeModel::zPrime()
  {
    return this->fPrime().sPrime().b();
  }

  /**
   * Rotate the whole cube about the z axis twice.
   */
  RubiksCube& RubiksCubeModel::z2()
  {
    return this->z().z();
  }
}

