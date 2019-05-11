#include "MoveStore.h"

namespace busybin
{
  /**
   * Init.
   */
  MoveStore::MoveStore(RubiksCube& cube) : pCube(&cube)
  {
  }

  /**
   * Get a move by index.
   * @param ind The move index.
   */
  RubiksCube::MOVE MoveStore::getMove(unsigned ind) const
  {
    return this->getMoves()[ind];
  }

  /**
   * Get a move by index.
   * @param ind The move index.
   */
  string MoveStore::getMoveString(unsigned ind) const
  {
    return this->pCube->getMove(this->getMoves()[ind]);
  }

  /**
   * Return the number of available moves.
   */
  unsigned MoveStore::getNumMoves() const
  {
    return this->getMoves().size();
  }

  /**
   * Make sure the string representation of a move is valid.
   * @param move The move enum.
   */
  bool MoveStore::isValidMove(RubiksCube::MOVE move) const
  {
    for (RubiksCube::MOVE m : this->getMoves())
    {
      if (move == m)
        return true;
    }

    return false;
  }

  /**
   * Move using an index.
   */
  void MoveStore::move(uint8_t ind)
  {
    this->pCube->move(this->getMove(ind));
  }

  /**
   * Undo a move.
   */
  void MoveStore::invert(uint8_t ind)
  {
    this->pCube->invert(this->getMove(ind));
  }
}

