#ifndef _BUSYBIN_RUBIKS_CUBE_MODEL3_H_ // TODO
#define _BUSYBIN_RUBIKS_CUBE_MODEL3_H_ // TODO

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
   * The sides:
   *
   *     U
   *   L F R B
   *     D
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
   */
  class RubiksCubeModel3
  {
    typedef char uchar;

  public:
    enum class FACE  : uchar {UP, LEFT, FRONT, RIGHT, BACK, DOWN};
    enum class COLOR : uchar {WHITE, GREEN, RED, BLUE, ORANGE, YELLOW};
    enum class CUBIE : uchar
    {
      UP_LEFT_BACK,    UP_BACK,    UP_RIGHT_BACK,
      UP_LEFT,         UP,         UP_RIGHT,
      UP_LEFT_FRONT,   UP_FRONT,   UP_RIGHT_FRONT,
      LEFT_BACK,       BACK,       RIGHT_BACK,
      LEFT,            RIGHT,
      LEFT_FRONT,      FRONT,      RIGHT_FRONT,
      DOWN_LEFT_BACK,  DOWN_BACK,  DOWN_RIGHT_BACK,
      DOWN_LEFT,       DOWN,       DOWN_RIGHT,
      DOWN_LEFT_FRONT, DOWN_FRONT, DOWN_RIGHT_FRONT
    };

  private:
    array<COLOR, 48> cube;
    array<COLOR, 6>  centers;

    inline void roll90(FACE f);
    inline void roll180(FACE f);
    inline void roll270(FACE f);

    inline void rotate90(unsigned s_i0, unsigned s_i1, unsigned s_i2, unsigned s_i3,
      unsigned c_i0, unsigned c_i1, unsigned c_i2, unsigned c_i3);
    inline void rotate180(unsigned s_i0, unsigned s_i1, unsigned s_i2, unsigned s_i3,
      unsigned c_i0, unsigned c_i1, unsigned c_i2, unsigned c_i3);

  public:
    RubiksCubeModel3();

    COLOR get(FACE face, unsigned row, unsigned col) const;
    
    RubiksCubeModel3& u();
    RubiksCubeModel3& uPrime();
    RubiksCubeModel3& u2();

    RubiksCubeModel3& l();
    RubiksCubeModel3& lPrime();
    RubiksCubeModel3& l2();

    RubiksCubeModel3& f();
    RubiksCubeModel3& fPrime();
    RubiksCubeModel3& f2();

    RubiksCubeModel3& r();
    RubiksCubeModel3& rPrime();
    RubiksCubeModel3& r2();

    RubiksCubeModel3& b();
    RubiksCubeModel3& bPrime();
    RubiksCubeModel3& b2();

    RubiksCubeModel3& d();
    RubiksCubeModel3& dPrime();
    RubiksCubeModel3& d2();
  };
}

#endif

