#include "TwistStore.h"

namespace busybin
{
  /**
   * Init.
   */
  TwistStore::TwistStore(RubiksCube& cube) :
    MoveStore(cube),
    moves
    ({
      RubiksCube::MOVE::L, RubiksCube::MOVE::LPRIME, RubiksCube::MOVE::L2,
      RubiksCube::MOVE::R, RubiksCube::MOVE::RPRIME, RubiksCube::MOVE::R2,
      RubiksCube::MOVE::U, RubiksCube::MOVE::UPRIME, RubiksCube::MOVE::U2,
      RubiksCube::MOVE::D, RubiksCube::MOVE::DPRIME, RubiksCube::MOVE::D2,
      RubiksCube::MOVE::F, RubiksCube::MOVE::FPRIME, RubiksCube::MOVE::F2,
      RubiksCube::MOVE::B, RubiksCube::MOVE::BPRIME, RubiksCube::MOVE::B2
    })
  {
  }

  /**
   * Return the list of available moves.
   */
  const vector<RubiksCube::MOVE>& TwistStore::getMoves() const
  {
    return this->moves;
  }

  /**
   * Move using an index.
   */
  void TwistStore::move(uint8_t ind)
  {
    this->pCube->move((RubiksCube::MOVE)ind);
  }

  /**
   * Undo a move.
   */
  void TwistStore::invert(uint8_t ind)
  {
    this->pCube->invert((RubiksCube::MOVE)ind);
  }
}

