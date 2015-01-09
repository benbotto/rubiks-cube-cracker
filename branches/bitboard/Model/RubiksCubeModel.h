#ifndef _BUSYBIN_RUBIKS_CUBE_MODEL_H_
#define _BUSYBIN_RUBIKS_CUBE_MODEL_H_

#include <array>
using std::array;
#include <set>
using std::set;
#include <algorithm>
using std::fill;
using std::next;
using std::set_intersection;
using std::next_permutation;
#include <utility>
using std::swap;
#include <iterator>
using std::advance;

namespace busybin
{
  /**
   * A raw Rubik's Cube model.  This is _not_ what is drawn.  It's a fairly
   * fast Rubik's Cube model used by the solver, and kept in sync with the
   * drawable Rubik's Cube WorldObject.
   */
  class RubiksCubeModel
  {
  public:
    enum class FACE  : unsigned char {UP, LEFT, FRONT, RIGHT, BACK, DOWN};
    enum class COLOR : char {WHITE = 'W', GREEN  = 'G', RED    = 'R',
                             BLUE  = 'B', ORANGE = 'O', YELLOW = 'Y'};

    typedef COLOR           CenterCubie;
    typedef array<COLOR, 2> EdgeCubie;
    typedef array<COLOR, 3> CornerCubie;

  private:
    // Note: poor man's hash table.  This was significantly faster than
    // an unordered_map with the same hash function (over twice as fast).
    typedef array<unsigned, 6> centerMap;
    // 42 == 5 << 3 | 4 (6 faces, 0-5).
    typedef array<array<unsigned, 2>, 42> edgeMap;
    // 355 = (5 << 6) | (4 << 3) | 3
    typedef array<array<unsigned, 3>, 355> cornerMap;

    array<COLOR, 54> cube;
    centerMap        centerCubies;
    edgeMap          edgeCubies;
    cornerMap        cornerCubies;

    void permuteEdge(array<FACE, 2> faces, array<unsigned, 2> indices);
    void permuteCorner(array<FACE, 3> faces, array<unsigned, 3> indices);

    unsigned hashCubie(FACE f1, FACE f2) const;
    unsigned hashCubie(FACE f1, FACE f2, FACE f3) const;
  public:
    RubiksCubeModel();

    COLOR get(unsigned i) const;
    COLOR get(FACE face, unsigned row, unsigned col) const;

    CenterCubie getCubie(FACE f1) const;
    EdgeCubie   getCubie(FACE f1, FACE f2) const;
    CornerCubie getCubie(FACE f1, FACE f2, FACE f3) const;

    bool isSolved() const;
    bool isSolved(FACE f1, FACE f2) const;
    bool isSolved(FACE f1, FACE f2, FACE f3) const;

    RubiksCubeModel& u();
    RubiksCubeModel& uPrime();
    RubiksCubeModel& u2();

    RubiksCubeModel& d();
    RubiksCubeModel& dPrime();
    RubiksCubeModel& d2();

    RubiksCubeModel& l();
    RubiksCubeModel& lPrime();
    RubiksCubeModel& l2();

    RubiksCubeModel& r();
    RubiksCubeModel& rPrime();
    RubiksCubeModel& r2();

    RubiksCubeModel& f();
    RubiksCubeModel& fPrime();
    RubiksCubeModel& f2();

    RubiksCubeModel& b();
    RubiksCubeModel& bPrime();
    RubiksCubeModel& b2();

    RubiksCubeModel& m();
    RubiksCubeModel& mPrime();
    RubiksCubeModel& m2();

    RubiksCubeModel& e();
    RubiksCubeModel& ePrime();
    RubiksCubeModel& e2();

    RubiksCubeModel& s();
    RubiksCubeModel& sPrime();
    RubiksCubeModel& s2();

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

