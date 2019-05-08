#include "G1TwistStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCube reference.
   */
  G1TwistStore::G1TwistStore(RubiksCube& cube) :
    MoveStore(cube),
    moves
    ({
      RubiksCube::MOVE::L,
      RubiksCube::MOVE::R,
      RubiksCube::MOVE::U2,
      RubiksCube::MOVE::D2,
      RubiksCube::MOVE::F,
      RubiksCube::MOVE::B
    })
  {
  }

  /**
   * Return the list of available moves.
   */
  const vector<RubiksCube::MOVE>& G1TwistStore::getMoves() const
  {
    return this->moves;
  }
}

