#include "TwistStore.h"

namespace busybin
{
  /**
   * Init.
   */
  TwistStore::TwistStore() :
    moves
    ({{
      "L", "L'", "L2",
      "R", "R'", "R2",
      "U", "U'", "U2",
      "D", "D'", "D2",
      "F", "F'", "F2",
      "B", "B'", "B2"
    }}),
    inverseMoves
    ({
      {"L", "L'"}, {"L'", "L"}, {"L2", "L2"},
      {"R", "R'"}, {"R'", "R"}, {"R2", "R2"},
      {"U", "U'"}, {"U'", "U"}, {"U2", "U2"},
      {"D", "D'"}, {"D'", "D"}, {"D2", "D2"},
      {"F", "F'"}, {"F'", "F"}, {"F2", "F2"},
      {"B", "B'"}, {"B'", "B"}, {"B2", "B2"}
    })
  {
  }

  /**
   * Overloded ctor which allows for passing in a custom
   * set of moves.
   * @param moves A vector of moves.
   */
  TwistStore::TwistStore(const vector<string>& moves) :
    moves(moves),
    inverseMoves
    ({
      {"L", "L'"}, {"L'", "L"}, {"L2", "L2"},
      {"R", "R'"}, {"R'", "R"}, {"R2", "R2"},
      {"U", "U'"}, {"U'", "U"}, {"U2", "U2"},
      {"D", "D'"}, {"D'", "D"}, {"D2", "D2"},
      {"F", "F'"}, {"F'", "F"}, {"F2", "F2"},
      {"B", "B'"}, {"B'", "B"}, {"B2", "B2"}
    })
  {
  }

  /**
   * Return the list of available moves.
   */
  const vector<string>& TwistStore::getMoves() const
  {
    return this->moves;
  }

  /**
   * Get the list of inverse moves.
   */
  const MoveStore::invMove_t& TwistStore::getInverseMoves() const
  {
    return this->inverseMoves;
  }
}

