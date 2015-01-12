#ifndef _BUSYBIN_RUBIKS_CUBE_MODEL3_H_ // TODO
#define _BUSYBIN_RUBIKS_CUBE_MODEL3_H_ // TODO

#include "../Util/RubiksCubeException.h"
#include <array>
using std::array;
#include <algorithm>
using std::fill;
using std::next;
#include <iterator>
using std::advance;
#include <cstdint>

namespace busybin
{
  /**
   * A raw Rubik's Cube model.  This is _not_ what is drawn.  It's a fairly
   * fast Rubik's Cube model used by the solver, and kept in sync with the
   * drawable Rubik's Cube WorldObject.
   */
  class RubiksCubeModel3 // TODO
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
    void roll180(FACE f);
    void roll270(FACE f);

    //inline void rotate90(unsigned i0, unsigned i02, unsigned i1, unsigned i12, unsigned i2, unsigned i22, unsigned i3, unsigned i32);
    inline void rotate90(unsigned s_i0, unsigned s_i1, unsigned s_i2, unsigned s_i3,
      unsigned c_i0, unsigned c_i1, unsigned c_i2, unsigned c_i3);

  public:
    RubiksCubeModel3(); // TODO
    //unsigned getFace(FACE f) const;

    //COLOR get(unsigned i) const;
    COLOR get(FACE face, unsigned row, unsigned col) const; // TODO 
    
    RubiksCubeModel3& u();

    RubiksCubeModel3& l();

    RubiksCubeModel3& f();

    RubiksCubeModel3& r();

    RubiksCubeModel3& b();
  };
}

#endif

