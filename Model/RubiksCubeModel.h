#ifndef _BUSYBIN_RUBIKS_CUBE_MODEL_H_
#define _BUSYBIN_RUBIKS_CUBE_MODEL_H_

#include "RubiksCube.h"
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
#include <cstring>
using std::memcpy;

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
  class RubiksCubeModel : public RubiksCube
  {
    typedef RubiksCube::FACE FACE;
    typedef RubiksCube::COLOR COLOR;

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
    typedef array<RubiksCube::COLOR, 3> corner_t;
    typedef array<RubiksCube::COLOR, 2> edge_t;

    RubiksCubeModel();
    RubiksCubeModel(const RubiksCubeModel& cube);

    COLOR getColor(FACE face, unsigned row, unsigned col) const;
    COLOR getColor(unsigned ind) const;
    edge_t getEdgeColors(RubiksCube::EDGE ind) const;
    corner_t getCornerColors(RubiksCube::CORNER ind) const;
    uint64_t getFace(FACE face) const;

    bool isSolved() const;

    // Indexing methods.
    uint8_t getCornerIndex(RubiksCube::CORNER ind) const;
    uint8_t getCornerOrientation(RubiksCube::CORNER ind) const;
    uint8_t getEdgeIndex(RubiksCube::EDGE ind) const;
    uint8_t getEdgeOrientation(RubiksCube::EDGE ind) const;

    // Compare this cube to another.
    bool operator<(const RubiksCubeModel& rhs) const;
    bool operator==(const RubiksCubeModel& rhs) const;

    // Copy.
    RubiksCubeModel& operator=(const RubiksCubeModel rhs);

    // Face moves.
    RubiksCube& u();
    RubiksCube& uPrime();
    RubiksCube& u2();

    RubiksCube& l();
    RubiksCube& lPrime();
    RubiksCube& l2();

    RubiksCube& f();
    RubiksCube& fPrime();
    RubiksCube& f2();

    RubiksCube& r();
    RubiksCube& rPrime();
    RubiksCube& r2();

    RubiksCube& b();
    RubiksCube& bPrime();
    RubiksCube& b2();

    RubiksCube& d();
    RubiksCube& dPrime();
    RubiksCube& d2();

    // Slice moves.
    RubiksCube& m();
    RubiksCube& mPrime();
    RubiksCube& m2();

    RubiksCube& e();
    RubiksCube& ePrime();
    RubiksCube& e2();

    RubiksCube& s();
    RubiksCube& sPrime();
    RubiksCube& s2();

    // Move the entire cube.  These moves are implemented in terms of
    // the moves above, and are therefore slower.
    RubiksCube& y();
    RubiksCube& y2();
    RubiksCube& yPrime();

    RubiksCube& x();
    RubiksCube& xPrime();
    RubiksCube& x2();

    RubiksCube& z();
    RubiksCube& zPrime();
    RubiksCube& z2();
  };
}

#endif

