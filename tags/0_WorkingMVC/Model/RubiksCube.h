#ifndef _BUSYBIN_RUBIKS_CUBE_H_
#define _BUSYBIN_RUBIKS_CUBE_H_

#include "../Util/RubiksCubeException.h"
#include <array>
using std::array;
#include <algorithm>
using std::fill;
using std::next;
#include <iterator>
using std::advance;

namespace busybin
{
  class RubiksCube
  {
  public:
    enum class FACE  : unsigned char {UP, LEFT, FRONT, RIGHT, BACK, DOWN};
    enum class COLOR : char {WHITE = 'W', GREEN  = 'G', RED    = 'R',
                             BLUE  = 'B', ORANGE = 'O', YELLOW = 'Y'};

  private:
    array<COLOR, 54> cube;

  public:
    RubiksCube();

    COLOR get(unsigned i) const;
    COLOR get(FACE face, unsigned row, unsigned col) const;

    RubiksCube& u();
    RubiksCube& uPrime();
    RubiksCube& u2();

    RubiksCube& d();
    RubiksCube& dPrime();
    RubiksCube& d2();

    RubiksCube& l();
    RubiksCube& lPrime();
    RubiksCube& l2();

    RubiksCube& r();
    RubiksCube& rPrime();
    RubiksCube& r2();

    RubiksCube& f();
    RubiksCube& fPrime();
    RubiksCube& f2();

    RubiksCube& b();
    RubiksCube& bPrime();
    RubiksCube& b2();
  };
}

#endif

