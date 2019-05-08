#include "G3TwistStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCube reference.
   */
  G3TwistStore::G3TwistStore(RubiksCube& cube) :
    MoveStore(cube),
    moves
    ({
      RubiksCube::MOVE::L2,
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
  const vector<RubiksCube::MOVE>& G3TwistStore::getMoves() const
  {
    return this->moves;
  }
}

