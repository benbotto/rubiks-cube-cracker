#include "RotationStore.h"

namespace busybin
{
  /**
   * Init.
   */
  RotationStore::RotationStore() :
    moves
    ({{
      "X", "X'", "X2",
      "Y", "Y'", "Y2",
      "Z", "Z'", "Z2",
    }}),
    inverseMoves
    ({
      {"X",  "X'"}, {"X'", "X"}, {"X2", "X2"},
      {"Y",  "Y'"}, {"Y'", "Y"}, {"Y2", "Y2"},
      {"Z",  "Z'"}, {"Z'", "Z"}, {"Z2", "Z2"}
    })
  {
  }

  /**
   * Return the list of available moves.
   */
  const vector<string>& RotationStore::getMoves() const
  {
    return this->moves;
  }

  /**
   * Get the list of inverse moves.
   */
  const MoveStore::invMove_t& RotationStore::getInverseMoves() const
  {
    return this->inverseMoves;
  }

  /**
   * Return the number of available moves.
   */
  unsigned RotationStore::getNumMoves() const
  {
    return 9;
  }
}

