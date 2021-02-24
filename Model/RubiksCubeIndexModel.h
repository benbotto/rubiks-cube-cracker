#ifndef _BUSYBIN_RUBIKS_CUBE_INDEX_MODEL_H_
#define _BUSYBIN_RUBIKS_CUBE_INDEX_MODEL_H_

#include "RubiksCube.h"
#include "RubiksCubeModel.h"
#include "../Util/RubiksCubeException.h"
#include <array>
using std::array;
#include <algorithm>
using std::swap;
#include <cstdint>

namespace busybin
{
  /**
   * A RubiksCubeModel that is optimized for fast moves and pattern database
   * indexing.  It stores each cubie as an index and orientation, with edges
   * and corners in separate arrays.
   *
   * Note that the cube is oriented with red on top and white up front, which
   * is how the solver is set up and differs from the RubiksCubeModel.
   *
   * Edge indexes.
   *
   * 0  1  2  3  4  5  6  7  8  9  10 11
   * UB UR UF UL FR FL BL BR DF DL DB DR
   * RY RG RW RB WG WB YB YG OW OB OY OG
   *
   * Corner indexes.
   *
   * 0   1   2   3   4   5   6   7
   * ULB URB URF ULF DLF DLB DRB DRF
   * RBY RGY RGW RBW OBW OBY OGY OGW
   */
  class RubiksCubeIndexModel : public RubiksCube
  {
    typedef RubiksCube::FACE FACE;
    typedef RubiksCube::COLOR COLOR;

  public:
    struct Cubie
    {
      // 0 - 11 for edges, 0 - 7 for corners.
      uint8_t index;
      // 0 - 1 for edges, 0 - 2 for corners.
      uint8_t orientation;
    };

  private:
    array<Cubie, 12> edges;
    array<Cubie, 8>  corners;
    array<COLOR, 6>  centers;

    inline void updateCornerOrientation(RubiksCube::CORNER ind, uint8_t amount);
    inline void updateEdgeOrientationZ(EDGE ind);

  public:
    RubiksCubeIndexModel();
    RubiksCubeIndexModel(const RubiksCubeModel& cube);

    array<COLOR, 2> getEdgeColors(EDGE ind) const;
    array<COLOR, 3> getCornerColors(CORNER ind) const;
    COLOR getColor(FACE face, unsigned row, unsigned col) const;

    // Indexing methods.
    uint8_t getEdgeIndex(EDGE ind) const;
    uint8_t getEdgeOrientation(EDGE ind) const;
    uint8_t getCornerIndex(CORNER ind) const;
    uint8_t getCornerOrientation(CORNER ind) const;

    bool isSolved() const;

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

    // Slice moves (not implemented).
    RubiksCube& m();
    RubiksCube& mPrime();
    RubiksCube& m2();

    RubiksCube& e();
    RubiksCube& ePrime();
    RubiksCube& e2();

    RubiksCube& s();
    RubiksCube& sPrime();
    RubiksCube& s2();

    // Full-cube moves (not implemented).
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

