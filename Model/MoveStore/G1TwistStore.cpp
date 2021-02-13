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
      RubiksCube::MOVE::LPRIME,
      RubiksCube::MOVE::L2,
      RubiksCube::MOVE::R,
      RubiksCube::MOVE::RPRIME,
      RubiksCube::MOVE::R2,
      RubiksCube::MOVE::U,
      RubiksCube::MOVE::UPRIME,
      RubiksCube::MOVE::U2,
      RubiksCube::MOVE::D,
      RubiksCube::MOVE::DPRIME,
      RubiksCube::MOVE::D2,
      RubiksCube::MOVE::F2,
      RubiksCube::MOVE::B2
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

