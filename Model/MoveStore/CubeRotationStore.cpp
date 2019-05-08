#include "CubeRotationStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCube reference for storing the move
   *        string->function map.
   */
  CubeRotationStore::CubeRotationStore(RubiksCubeWorldObject& cube)
  {
    // Set up the rotation map.
    this->moveMap["X"]  = bind(&RubiksCubeWorldObject::x,      &cube);
    this->moveMap["X'"] = bind(&RubiksCubeWorldObject::xPrime, &cube);
    this->moveMap["X2"] = bind(&RubiksCubeWorldObject::x2,     &cube);

    this->moveMap["Y"]  = bind(&RubiksCubeWorldObject::y,      &cube);
    this->moveMap["Y'"] = bind(&RubiksCubeWorldObject::yPrime, &cube);
    this->moveMap["Y2"] = bind(&RubiksCubeWorldObject::y2,     &cube);

    this->moveMap["Z"]  = bind(&RubiksCubeWorldObject::z,      &cube);
    this->moveMap["Z'"] = bind(&RubiksCubeWorldObject::zPrime, &cube);
    this->moveMap["Z2"] = bind(&RubiksCubeWorldObject::z2,     &cube);
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

