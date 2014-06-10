#include "MoveStore.h"

namespace busybin
{
  /**
   * Init.
   */
  MoveStore::MoveStore() :
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
    }),
    rotations
    ({{
      "X", "X'", "X2",
      "Y", "Y'", "Y2",
      "Z", "Z'", "Z2",
    }}),
    inverseRotations
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
  const array<string, 18>& MoveStore::getMoves() const
  {
    return this->moves;
  }

  /**
   * Get a move by index.
   * @param ind The move index.
   */
  string MoveStore::getMove(unsigned ind) const
  {
    if (ind >= this->moves.size())
      throw RubiksCubeException("Index out of bounds in MoveStore::getMove.");

    return this->moves.at(ind);
  }

  /**
   * Get the inverse of a move (e.g. the inverse of L is L').
   * @param move The move for which the inverse shall be returned.
   */
  string MoveStore::getInverseMove(const string& move) const
  {
    if (!this->inverseMoves.count(move))
      throw RubiksCubeException("Index out of bounds in MoveStore::getInverseMove.");

    return this->inverseMoves.at(move);
  }

  /**
   * Return the number of available moves.
   */
  unsigned MoveStore::getNumMoves() const
  {
    return this->moves.size();
  }

  /**
   * Get the move function in the cube passed to the constructor
   * based on the string representation.
   * @param string The string representation of the move.
   */
  MoveStore::moveFunc_t& MoveStore::getMoveFunc(const string& move)
  {
    if (!this->getMoveMap().count(move))
      throw RubiksCubeException("Invalid move in MoveStore::getMoveFunc.");

    return this->getMoveMap()[move];
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

  /**
   * Return the list of available rotations.
   */
  const array<string, 9>& MoveStore::getRotations() const
  {
    return this->rotations;
  }

  /**
   * Get a rotation by index.
   * @param ind The rotation index.
   */
  string MoveStore::getRotation(unsigned ind) const
  {
    if (ind >= this->rotations.size())
      throw RubiksCubeException("Index out of bounds in MoveStore::getRotation.");

    return this->rotations.at(ind);
  }

  /**
   * Get the inverse of a rotation (e.g. the inverse of L is L').
   * @param rotation The rotation for which the inverse shall be returned.
   */
  string MoveStore::getInverseRotation(const string& rotation) const
  {
    if (!this->inverseRotations.count(rotation))
      throw RubiksCubeException("Index out of bounds in MoveStore::getInverseRotation.");

    return this->inverseRotations.at(rotation);
  }

  /**
   * Return the number of available rotations.
   */
  unsigned MoveStore::getNumRotations() const
  {
    return this->rotations.size();
  }

  /**
   * Get the rotation function in the cube passed to the constructor
   * based on the string representation.
   * @param string The string representation of the rotation.
   */
  MoveStore::rotFunc_t& MoveStore::getRotationFunc(const string& rotation)
  {
    if (!this->getRotationMap().count(rotation))
      throw RubiksCubeException("Invalid rotation in MoveStore::getRotationFunc.");

    return this->getRotationMap()[rotation];
  }

  /**
   * Get the inverse rotation function corresponding to rotation.
   * @param string The string representation of the rotation for which the inverse
   *        rotation function shall be returned.
   */
  MoveStore::rotFunc_t& MoveStore::getInverseRotationFunc(const string& rotation)
  {
    return this->getRotationMap()[this->getInverseRotation(rotation)];
  }

  /**
   * Make sure the string representation of a rotation is valid.
   * @param string The string representation of the rotation.
   */
  bool MoveStore::isValidRotation(const string& rotation) const
  {
    return this->getRotationMap().count(rotation) == 1;
  }
}

