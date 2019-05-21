#include "G2TwistStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCube reference.
   */
  G2TwistStore::G2TwistStore(RubiksCube& cube) :
    MoveStore(cube),
    moves
    ({
      RubiksCube::MOVE::L,
      RubiksCube::MOVE::LPRIME,
      RubiksCube::MOVE::L2,
      RubiksCube::MOVE::R,
      RubiksCube::MOVE::RPRIME,
      RubiksCube::MOVE::R2,
      RubiksCube::MOVE::U2,
      RubiksCube::MOVE::D2,
      RubiksCube::MOVE::F2,
      RubiksCube::MOVE::B2
    })
  {
  }

  /**
   * Return the list of available moves.
   */
  const vector<RubiksCube::MOVE>& G2TwistStore::getMoves() const
  {
    return this->moves;
  }
}

