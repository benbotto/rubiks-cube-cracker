#ifndef _BUSYBIN_RUBIKS_CUBE_H_
#define _BUSYBIN_RUBIKS_CUBE_H_

#include "../Util/RubiksCubeException.h"
#include <array>
using std::array;
#include <set>
using std::set;
#include <map>
using std::map;
#include <algorithm>
using std::fill;
using std::next;
using std::set_intersection;
using std::next_permutation;
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

    typedef COLOR           CenterCubie;
    typedef array<COLOR, 2> EdgeCubie;
    typedef array<COLOR, 3> CornerCubie;

  private:
    typedef map<FACE, unsigned> centerMap;
    typedef map<array<FACE, 2>, array<unsigned, 2> > edgeMap;
    typedef map<array<FACE, 3>, array<unsigned, 3> > cornerMap;

    array<COLOR, 54> cube;
    centerMap        centerCubies;
    edgeMap          edgeCubies;
    cornerMap        cornerCubies;

    void permuteEdge(array<FACE, 2> faces, array<unsigned, 2> indices);
    void permuteCorner(array<FACE, 3> faces, array<unsigned, 3> indices);
  public:
    RubiksCube();

    COLOR get(unsigned i) const;
    COLOR get(FACE face, unsigned row, unsigned col) const;

    CenterCubie getCubie(FACE f1) const;
    EdgeCubie   getCubie(FACE f1, FACE f2) const;
    CornerCubie getCubie(FACE f1, FACE f2, FACE f3) const;

    bool isSolved() const;
    bool isSolved(FACE f1, FACE f2) const;
    bool isSolved(FACE f1, FACE f2, FACE f3) const;

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

    RubiksCube& m();
    RubiksCube& mPrime();
    RubiksCube& m2();

    RubiksCube& e();
    RubiksCube& ePrime();
    RubiksCube& e2();

    RubiksCube& s();
    RubiksCube& sPrime();
    RubiksCube& s2();

    RubiksCube& rotateLeft();
    RubiksCube& rotateRight();
    RubiksCube& rotateUp();
    RubiksCube& rotateDown();
  };
}

#endif

