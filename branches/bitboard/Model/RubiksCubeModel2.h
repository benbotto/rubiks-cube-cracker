#ifndef _BUSYBIN_RUBIKS_CUBE_MODEL2_H_ // TODO
#define _BUSYBIN_RUBIKS_CUBE_MODEL2_H_ // TODO

#include "../Util/RubiksCubeException.h"
#include <array>
using std::array;

namespace busybin
{
  /**
   * A raw Rubik's Cube model.  This is _not_ what is drawn.  It's a fairly
   * fast Rubik's Cube model used by the solver, and kept in sync with the
   * drawable Rubik's Cube WorldObject.
   */
  class RubiksCubeModel2 // TODO
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
    array<unsigned, 6>  faces;
    unsigned            centers;
    array<unsigned, 54> faceMasks; // TODO: These might not get used.
    array<unsigned, 54> faceShifts;

    void roll90(FACE f);
    void roll180(FACE f);
    void roll270(FACE f);

  public:
    RubiksCubeModel2(); // TODO
    unsigned getFace(FACE f) const;

    //COLOR get(unsigned i) const;
    COLOR get(FACE face, unsigned row, unsigned col) const; // TODO
    
    RubiksCubeModel2& u();

    RubiksCubeModel2& l();

    RubiksCubeModel2& f();
  };
}

#endif

