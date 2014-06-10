#include "CubeMoveStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCube reference for storing the move
   *        string->function map.
   */
  CubeMoveStore::CubeMoveStore(RubiksCube& cube)
  {
    // Set up the move map.
    this->moveMap["L"]  = bind(&RubiksCube::l,      &cube);
    this->moveMap["L'"] = bind(&RubiksCube::lPrime, &cube);
    this->moveMap["L2"] = bind(&RubiksCube::l2,     &cube);

    this->moveMap["R"]  = bind(&RubiksCube::r,      &cube);
    this->moveMap["R'"] = bind(&RubiksCube::rPrime, &cube);
    this->moveMap["R2"] = bind(&RubiksCube::r2,     &cube);

    this->moveMap["U"]  = bind(&RubiksCube::u,      &cube);
    this->moveMap["U'"] = bind(&RubiksCube::uPrime, &cube);
    this->moveMap["U2"] = bind(&RubiksCube::u2,     &cube);

    this->moveMap["D"]  = bind(&RubiksCube::d,      &cube);
    this->moveMap["D'"] = bind(&RubiksCube::dPrime, &cube);
    this->moveMap["D2"] = bind(&RubiksCube::d2,     &cube);

    this->moveMap["F"]  = bind(&RubiksCube::f,      &cube);
    this->moveMap["F'"] = bind(&RubiksCube::fPrime, &cube);
    this->moveMap["F2"] = bind(&RubiksCube::f2,     &cube);

    this->moveMap["B"]  = bind(&RubiksCube::b,      &cube);
    this->moveMap["B'"] = bind(&RubiksCube::bPrime, &cube);
    this->moveMap["B2"] = bind(&RubiksCube::b2,     &cube);

    // Set up the rotation map.
    this->rotMap["X"]  = bind(&RubiksCube::x,      &cube);
    this->rotMap["X'"] = bind(&RubiksCube::xPrime, &cube);
    this->rotMap["X2"] = bind(&RubiksCube::x2,     &cube);

    this->rotMap["Y"]  = bind(&RubiksCube::y,      &cube);
    this->rotMap["Y'"] = bind(&RubiksCube::yPrime, &cube);
    this->rotMap["Y2"] = bind(&RubiksCube::y2,     &cube);

    this->rotMap["Z"]  = bind(&RubiksCube::z,      &cube);
    this->rotMap["Z'"] = bind(&RubiksCube::zPrime, &cube);
    this->rotMap["Z2"] = bind(&RubiksCube::z2,     &cube);
  }

  /**
   * Get a move map with the string representation of a move
   * to the corresponding move function in the cube passed
   * to the constructor.
   */
  MoveStore::moveMap_t& CubeMoveStore::getMoveMap()
  {
    return this->moveMap;
  }

  /**
   * Constant version of the above.
   */
  const MoveStore::moveMap_t& CubeMoveStore::getMoveMap() const
  {
    return this->moveMap;
  }

  /**
   * Get a rotation map with the string representation of a rotation
   * to the corresponding rotation function in the cube passed
   * to the constructor.
   */
  MoveStore::rotMap_t& CubeMoveStore::getRotationMap()
  {
    return this->rotMap;
  }

  /**
   * Constant version of the above.
   */
  const MoveStore::rotMap_t& CubeMoveStore::getRotationMap() const
  {
    return this->rotMap;
  }
}

