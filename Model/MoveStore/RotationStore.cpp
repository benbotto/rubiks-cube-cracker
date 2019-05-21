#include "RotationStore.h"

namespace busybin
{
  /**
   * Init.
   */
  RotationStore::RotationStore(RubiksCube& cube) :
    MoveStore(cube),
    moves
    ({
      RubiksCube::MOVE::X, RubiksCube::MOVE::XPRIME, RubiksCube::MOVE::X2,
      RubiksCube::MOVE::Y, RubiksCube::MOVE::YPRIME, RubiksCube::MOVE::Y2,
      RubiksCube::MOVE::Z, RubiksCube::MOVE::ZPRIME, RubiksCube::MOVE::Z2
    })
  {
  }

  /**
   * Return the list of available moves.
   */
  const vector<RubiksCube::MOVE>& RotationStore::getMoves() const
  {
    return this->moves;
  }
}

