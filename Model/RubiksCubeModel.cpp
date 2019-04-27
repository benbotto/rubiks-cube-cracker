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
   * @param row The 0-based row, unfolded as described in get(i).
   * @param col The 0-based col, unfulded as described in get(i).
   */
  RubiksCubeModel::COLOR RubiksCubeModel::get(
    FACE f, unsigned row, unsigned col) const
  {
    if (row == 1 and col == 1)
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
   * Get an entire face of the cube as a 64-bit int.
   * @param face The face to get.
   */
  uint64_t RubiksCubeModel::getFace(FACE face) const
  {
    return *(uint64_t*)&this->cube[(unsigned)face * 8];
  }

  /**
   * Compare two cubes (integer comparison of each side).
   */
  bool RubiksCubeModel::operator<(const RubiksCubeModel& rhs) const
  {
    for (uchar i = 0; i < 6; ++i)
      if (this->getFace((FACE)i) < rhs.getFace((FACE)i))
        return true;

    return false;
  }

  /**
   * Move the up face clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::u()
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
  RubiksCubeModel& RubiksCubeModel::uPrime()
  {
    this->roll270(FACE::UP);
    this->rotateSides90(32, 24, 16, 8, 34, 26, 18, 10);
    return *this;
  }

  /**
   * Move the up face twice
   */
  RubiksCubeModel& RubiksCubeModel::u2()
  {
    this->roll180(FACE::UP);
    this->rotateSides180(8, 24, 16, 32, 10, 26, 18, 34);
    return *this;
  }

  /**
   * Move the left face clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::l()
  {
    this->roll90(FACE::LEFT);
    this->rotateSides90(6, 34, 46, 22, 0, 36, 40, 16);
    return *this;
  }

  /**
   * Move the left face counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::lPrime()
  {
    this->roll270(FACE::LEFT);
    this->rotateSides90(22, 46, 34, 6, 16, 40, 36, 0);
    return *this;
  }

  /**
   * Move the left face twice.
   */
  RubiksCubeModel& RubiksCubeModel::l2()
  {
    this->roll180(FACE::LEFT);
    this->rotateSides180(6, 46, 34, 22, 0, 40, 36, 16);
    return *this;
  }

  /**
   * Move the front face clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::f()
  {
    this->roll90(FACE::FRONT);
    this->rotateSides90(4, 10, 40, 30, 6, 12, 42, 24);
    return *this;
  }

  /**
   * Move the front face counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::fPrime()
  {
    this->roll270(FACE::FRONT);
    this->rotateSides90(30, 40, 10, 4, 24, 42, 12, 6);
    return *this;
  }

  /**
   * Move the front face twice.
   */
  RubiksCubeModel& RubiksCubeModel::f2()
  {
    this->roll180(FACE::FRONT);
    this->rotateSides180(4, 40, 10, 30, 6, 42, 12, 24);
    return *this;
  }

  /**
   * Move the right face clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::r()
  {
    this->roll90(FACE::RIGHT);
    this->rotateSides90(2, 18, 42, 38, 4, 20, 44, 32);
    return *this;
  }

  /**
   * Move the right face counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::rPrime()
  {
    this->roll270(FACE::RIGHT);
    this->rotateSides90(38, 42, 18, 2, 32, 44, 20, 4);
    return *this;
  }

  /**
   * Move the right face twice.
   */
  RubiksCubeModel& RubiksCubeModel::r2()
  {
    this->roll180(FACE::RIGHT);
    this->rotateSides180(2, 42, 18, 38, 4, 44, 20, 32);
    return *this;
  }

  /**
   * Move the back face clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::b()
  {
    this->roll90(FACE::BACK);
    this->rotateSides90(0, 26, 44, 14, 2, 28, 46, 8);
    return *this;
  }

  /**
   * Move the back face counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::bPrime()
  {
    this->roll270(FACE::BACK);
    this->rotateSides90(14, 44, 26, 0, 8, 46, 28, 2);
    return *this;
  }

  /**
   * Move the back face twice.
   */
  RubiksCubeModel& RubiksCubeModel::b2()
  {
    this->roll180(FACE::BACK);
    this->rotateSides180(0, 44, 26, 14, 2, 46, 28, 8);
    return *this;
  }

  /**
   * Move the down face clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::d()
  {
    this->roll90(FACE::DOWN);
    this->rotateSides90(12, 36, 28, 20, 14, 38, 30, 22);
    return *this;
  }

  /**
   * Move the down face counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::dPrime()
  {
    this->roll270(FACE::DOWN);
    this->rotateSides90(20, 28, 36, 12, 22, 30, 38, 14);
    return *this;
  }

  /**
   * Move the down face twice.
   */
  RubiksCubeModel& RubiksCubeModel::d2()
  {
    this->roll180(FACE::DOWN);
    this->rotateSides180(12, 28, 36, 20, 14, 30, 38, 22);
    return *this;
  }

  /**
   * Rotate the M slice clockwise (between R and L, same way as L).
   */
  RubiksCubeModel& RubiksCubeModel::m()
  {
    this->rotateSlice90(1, 37, 41, 17, 5, 33, 45, 21, 0, 4, 5, 2);
    return *this;
  }

  /**
   * Rotate the M slice counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::mPrime()
  {
    this->rotateSlice90(17, 41, 37, 1, 21, 45, 33, 5, 2, 5, 4, 0);
    return *this;
  }

  /**
   * Rotate the M slice twice.
   */
  RubiksCubeModel& RubiksCubeModel::m2()
  {
    this->rotateSlice180(1, 41, 37, 17, 5, 45, 33, 21, 0, 5, 4, 2);
    return *this;
  }

  /**
   * Rotate the E slice clockwise (between U and D, same way as D).
   */
  RubiksCubeModel& RubiksCubeModel::e()
  {
    this->rotateSlice90(15, 39, 31, 23, 11, 35, 27, 19, 1, 4, 3, 2);
    return *this;
  }

  /**
   * Rotate the E slice counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::ePrime()
  {
    this->rotateSlice90(23, 31, 39, 15, 19, 27, 35, 11, 2, 3, 4, 1);
    return *this;
  }

  /**
   * Rotate the E slice twice.
   */
  RubiksCubeModel& RubiksCubeModel::e2()
  {
    this->rotateSlice180(15, 31, 39, 23, 11, 27, 35, 19, 1, 3, 4, 2);
    return *this;
  }

  /**
   * Rotate the S slice clockwise (between B and F, same way as F).
   */
  RubiksCubeModel& RubiksCubeModel::s()
  {
    this->rotateSlice90(3, 9, 47, 29, 7, 13, 43, 25, 0, 1, 5, 3);
    return *this;
  }

  /**
   * Rotate the S slice counter clockwise.
   */
  RubiksCubeModel& RubiksCubeModel::sPrime()
  {
    this->rotateSlice90(29, 47, 9, 3, 25, 43, 13, 7, 3, 5, 1, 0);
    return *this;
  }

  /**
   * Rotate the S slice twice.
   */
  RubiksCubeModel& RubiksCubeModel::s2()
  {
    this->rotateSlice180(3, 47, 9, 29, 7, 43, 13, 25, 0, 5, 1, 3);
    return *this;
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
   * Rotate the whole cube about the x axis (e.g. down) counter clockwise 
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
   * Rotate the whole cube about the y axis (e.g. right) counter clockwise
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
   * Rotate the whole cube about the z axis (e.g. sideways) counter clockwise 
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

