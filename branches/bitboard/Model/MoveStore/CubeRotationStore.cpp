#include "CubeRotationStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCube reference for storing the move
   *        string->function map.
   */
  CubeRotationStore::CubeRotationStore(RubiksCube& cube)
  {
    // Set up the rotation map.
    this->moveMap["X"]  = bind(&RubiksCube::x,      &cube);
    this->moveMap["X'"] = bind(&RubiksCube::xPrime, &cube);
    this->moveMap["X2"] = bind(&RubiksCube::x2,     &cube);

    this->moveMap["Y"]  = bind(&RubiksCube::y,      &cube);
    this->moveMap["Y'"] = bind(&RubiksCube::yPrime, &cube);
    this->moveMap["Y2"] = bind(&RubiksCube::y2,     &cube);

    this->moveMap["Z"]  = bind(&RubiksCube::z,      &cube);
    this->moveMap["Z'"] = bind(&RubiksCube::zPrime, &cube);
    this->moveMap["Z2"] = bind(&RubiksCube::z2,     &cube);
  }

  /**
   * Get a move map with the string representation of a move
   * to the corresponding move function in the cube passed
   * to the constructor.
   */
  MoveStore::moveFuncMap_t& CubeRotationStore::getMoveMap()
  {
    return this->moveMap;
  }

  /**
   * Constant version of the above.
   */
  const MoveStore::moveFuncMap_t& CubeRotationStore::getMoveMap() const
  {
    return this->moveMap;
  }
}

