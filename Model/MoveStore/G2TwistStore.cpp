#include "G2TwistStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCube reference.  Quarter twists of U and D do not
   * change the orientation of corners, so they are permitted.
   */
  G2TwistStore::G2TwistStore(RubiksCube& cube) :
    MoveStore(cube),
    moves
    ({
      RubiksCube::MOVE::L2,
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
  const vector<RubiksCube::MOVE>& G2TwistStore::getMoves() const
  {
    return this->moves;
  }
}

