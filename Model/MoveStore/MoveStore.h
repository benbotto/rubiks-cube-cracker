#ifndef _BUSYBIN_MOVE_STORE_H_
#define _BUSYBIN_MOVE_STORE_H_

#include "../RubiksCube.h"
#include <vector>
using std::vector;
#include <string>
using std::string;

namespace busybin
{
  /**
   * A MoveStore holds a limited set of moves for a RubiksCube.  When solving
   * the cube, for example, some goals require all twists of the 6 faces,
   * others only need rotations, etc.
   */
  class MoveStore
  {
  protected:
    RubiksCube* pCube;

    virtual const vector<RubiksCube::MOVE>& getMoves() const = 0;

  public:
    MoveStore(RubiksCube& cube);

    RubiksCube::MOVE getMove(unsigned ind) const;
    string getMoveString(unsigned ind) const;
    unsigned getNumMoves() const;
    bool isValidMove(RubiksCube::MOVE move) const;
    virtual void move(uint8_t ind);
    virtual void invert(uint8_t ind);
  };
}

#endif

