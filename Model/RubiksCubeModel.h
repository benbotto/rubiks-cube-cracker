#ifndef _BUSYBIN_RUBIKS_CUBE_MODEL_H_
#define _BUSYBIN_RUBIKS_CUBE_MODEL_H_

#include "../Util/RubiksCubeException.h"
#include <array>
using std::array;
#include <algorithm>
using std::fill;
using std::next;
using std::swap;
#include <iterator>
using std::advance;
#include <cstdint>

namespace busybin
{
  /**
   * A raw Rubik's Cube model.  This is _not_ what is drawn.  It's a fairly
   * fast Rubik's Cube model used by the solver, and kept in sync with the
   * drawable Rubik's Cube WorldObject.
   *
   * The cube is laid out as follows.
   *
   * The sides:
   *
   *    U
   *  L F R B
   *    D
   *
   * Color wise:
   *
   *          W W W
   *          W W W
   *          W W W
   *
   *  G G G   R R R   B B B   O O O
   *  G G G   R R R   B B B   O O O
   *  G G G   R R R   B B B   O O O
   *
   *          Y Y Y
   *          Y Y Y
   *          Y Y Y
   *
   * Index wise:
   *
   *
   *              0  1  2
   *              7     3
   *              6  5  4
   *
   *   8  9 10   16 17 18   24 25 26   32 33 34
   *  15    11   23    19   31    27   39    35
   *  14 13 12   22 21 20   30 29 28   38 37 36
   *
   *             40 41 42
   *             47    43
   *             46 45 44
   *
   * Centers:
   *
   *    0
   *  1 2 3 4
   *    5
   */
  class RubiksCubeModel
  {
    typedef unsigned char uchar;

  public:
    enum class FACE  : uchar {UP, LEFT, FRONT, RIGHT, BACK, DOWN};
    enum class COLOR : uchar {WHITE, GREEN, RED, BLUE, ORANGE, YELLOW};

  private:
    array<COLOR, 48> cube;
    array<COLOR, 6>  centers;

    inline void roll90(FACE f);
    inline void roll180(FACE f);
    inline void roll270(FACE f);

    inline void rotateSides90(
      unsigned s_i0, unsigned s_i1, unsigned s_i2, unsigned s_i3,
      unsigned c_i0, unsigned c_i1, unsigned c_i2, unsigned c_i3);
    inline void rotateSides180(
      unsigned s_i0, unsigned s_i1, unsigned s_i2, unsigned s_i3,
      unsigned c_i0, unsigned c_i1, unsigned c_i2, unsigned c_i3);

    inline void rotateSlice90(
      unsigned c_fi0, unsigned c_fi1, unsigned c_fi2, unsigned c_fi3,
      unsigned c_fi4, unsigned c_fi5, unsigned c_fi6, unsigned c_fi7,
      unsigned c_ci0, unsigned c_ci1, unsigned c_ci2, unsigned c_ci3);
    inline void rotateSlice180(
      unsigned c_fi0, unsigned c_fi1, unsigned c_fi2, unsigned c_fi3,
      unsigned c_fi4, unsigned c_fi5, unsigned c_fi6, unsigned c_fi7,
      unsigned c_ci0, unsigned c_ci1, unsigned c_ci2, unsigned c_ci3);

  public:
    RubiksCubeModel();

    COLOR get(FACE face, unsigned row, unsigned col) const;
    uint64_t getFace(FACE face) const;

    // Compare this cube to another.
    bool operator<(const RubiksCubeModel& rhs) const;
    
    // Face moves.
    RubiksCubeModel& u();
    RubiksCubeModel& uPrime();
    RubiksCubeModel& u2();

    RubiksCubeModel& l();
    RubiksCubeModel& lPrime();
    RubiksCubeModel& l2();

    RubiksCubeModel& f();
    RubiksCubeModel& fPrime();
    RubiksCubeModel& f2();

    RubiksCubeModel& r();
    RubiksCubeModel& rPrime();
    RubiksCubeModel& r2();

    RubiksCubeModel& b();
    RubiksCubeModel& bPrime();
    RubiksCubeModel& b2();

    RubiksCubeModel& d();
    RubiksCubeModel& dPrime();
    RubiksCubeModel& d2();

    // Slice moves.
    RubiksCubeModel& m();
    RubiksCubeModel& mPrime();
    RubiksCubeModel& m2();

    RubiksCubeModel& e();
    RubiksCubeModel& ePrime();
    RubiksCubeModel& e2();

    RubiksCubeModel& s();
    RubiksCubeModel& sPrime();
    RubiksCubeModel& s2();

    // Move the entire cube.  These moves are implemented in terms of
    // the moves above, and are therefore slower.
    RubiksCubeModel& y();
    RubiksCubeModel& y2();
    RubiksCubeModel& yPrime();

    RubiksCubeModel& x();
    RubiksCubeModel& xPrime();
    RubiksCubeModel& x2();

    RubiksCubeModel& z();
    RubiksCubeModel& zPrime();
    RubiksCubeModel& z2();
  };
}

#endif

