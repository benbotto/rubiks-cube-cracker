#ifndef _BUSYBIN_RUBIKS_CUBE_H_
#define _BUSYBIN_RUBIKS_CUBE_H_

#include "../Util/RubiksCubeException.h"
#include <cstdint>
#include <string>
using std::string;

namespace busybin
{
  /**
   * A base class for all of the Rubik's Cubes.  There are various models that
   * are specialized for different things, and the shared functionality and
   * interface is defined here.
   */
  class RubiksCube
  {
  public:
    enum class FACE   : uint8_t {UP, LEFT, FRONT, RIGHT, BACK, DOWN};
    enum class COLOR  : uint8_t {WHITE, GREEN, RED, BLUE, ORANGE, YELLOW};
    enum class EDGE   : uint8_t {UB, UR, UF, UL, FR, FL, BL, BR, DF, DL, DB, DR};
    enum class CORNER : uint8_t {ULB, URB, URF, ULF, DLF, DLB, DRB, DRF};
    enum class MOVE   : uint8_t
    {
      L, LPRIME, L2,
      R, RPRIME, R2,
      U, UPRIME, U2,
      D, DPRIME, D2,
      F, FPRIME, F2,
      B, BPRIME, B2,
      Y, YPRIME, Y2,
      X, XPRIME, X2,
      Z, ZPRIME, Z2,
      M, MPRIME, M2,
      E, EPRIME, E2,
      S, SPRIME, S2
    };

    virtual COLOR getColor(FACE face, unsigned row, unsigned col) const = 0;
    virtual bool isSolved() const = 0;
    string getMove(MOVE ind) const;

    // Face moves.
    RubiksCube& move(MOVE ind);
    RubiksCube& invert(MOVE ind);

    virtual RubiksCube& u() = 0;
    virtual RubiksCube& uPrime() = 0;
    virtual RubiksCube& u2() = 0;

    virtual RubiksCube& l() = 0;
    virtual RubiksCube& lPrime() = 0;
    virtual RubiksCube& l2() = 0;

    virtual RubiksCube& f() = 0;
    virtual RubiksCube& fPrime() = 0;
    virtual RubiksCube& f2() = 0;

    virtual RubiksCube& r() = 0;
    virtual RubiksCube& rPrime() = 0;
    virtual RubiksCube& r2() = 0;

    virtual RubiksCube& b() = 0;
    virtual RubiksCube& bPrime() = 0;
    virtual RubiksCube& b2() = 0;

    virtual RubiksCube& d() = 0;
    virtual RubiksCube& dPrime() = 0;
    virtual RubiksCube& d2() = 0;

    // Slice moves.
    virtual RubiksCube& m() = 0;
    virtual RubiksCube& mPrime() = 0;
    virtual RubiksCube& m2() = 0;

    virtual RubiksCube& e() = 0;
    virtual RubiksCube& ePrime() = 0;
    virtual RubiksCube& e2() = 0;

    virtual RubiksCube& s() = 0;
    virtual RubiksCube& sPrime() = 0;
    virtual RubiksCube& s2() = 0;

    // Move the entire cube.  These moves are implemented in terms of
    // the moves above, and are therefore slower.
    virtual RubiksCube& y() = 0;
    virtual RubiksCube& y2() = 0;
    virtual RubiksCube& yPrime() = 0;

    virtual RubiksCube& x() = 0;
    virtual RubiksCube& xPrime() = 0;
    virtual RubiksCube& x2() = 0;

    virtual RubiksCube& z() = 0;
    virtual RubiksCube& zPrime() = 0;
    virtual RubiksCube& z2() = 0;
  };
}

#endif

