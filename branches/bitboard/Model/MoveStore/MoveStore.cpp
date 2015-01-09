#include "MoveStore.h"

namespace busybin
{
  /**
   * Init.
   */
  MoveStore::MoveStore()
  {
  }

  /**
   * Get a move by index.
   * @param ind The move index.
   */
  string MoveStore::getMove(unsigned ind) const
  {
    if (ind >= this->getNumMoves())
      throw RubiksCubeException("Index out of bounds in MoveStore::getMove.");

    return this->getMoves()[ind];
  }

  /**
   * Get the inverse of a move (e.g. the inverse of L is L').
   * @param move The move for which the inverse shall be returned.
   */
  string MoveStore::getInverseMove(const string& move) const
  {
    invMove_t::const_iterator iMoveIt = this->getInverseMoves().find(move);

    if (iMoveIt != this->getInverseMoves().end())
      return iMoveIt->second;
    else
      throw RubiksCubeException("Index out of bounds in MoveStore::getInverseMove.");
  }

  /**
   * Return the number of available moves.
   */
  unsigned MoveStore::getNumMoves() const
  {
    return this->getMoves().size();
  }

  /**
   * Get the move function in the cube passed to the constructor
   * based on the string representation.  If the move isn't found
   * in the move map, the rotation map is searched.
   * @param string The string representation of the move.
   */
  MoveStore::moveFunc_t& MoveStore::getMoveFunc(const string& move)
  {
    moveFuncMap_t::iterator mFuncIt = this->getMoveMap().find(move);

    if (mFuncIt != this->getMoveMap().end())
      return mFuncIt->second;
    else
      throw RubiksCubeException("Invalid move in MoveStore::getMoveFunc.");
  }

  /**
   * Get the inverse move function corresponding to move.
   * @param string The string representation of the move for which the inverse
   *        move function shall be returned.
   */
  MoveStore::moveFunc_t& MoveStore::getInverseMoveFunc(const string& move)
  {
    return this->getMoveMap()[this->getInverseMove(move)];
  }

  /**
   * Make sure the string representation of a move is valid.
   * @param string The string representation of the move.
   */
  bool MoveStore::isValidMove(const string& move) const
  {
    return this->getMoveMap().count(move) == 1;
  }
}

