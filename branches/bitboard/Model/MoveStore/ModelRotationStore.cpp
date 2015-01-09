#include "ModelRotationStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCubeModel reference for storing the move
   *        string->function map.
   */
  ModelRotationStore::ModelRotationStore(RubiksCubeModel& cube)
  {
    // Set up the rotation map.
    this->moveMap["X"]  = bind(&RubiksCubeModel::x,      &cube);
    this->moveMap["X'"] = bind(&RubiksCubeModel::xPrime, &cube);
    this->moveMap["X2"] = bind(&RubiksCubeModel::x2,     &cube);

    this->moveMap["Y"]  = bind(&RubiksCubeModel::y,      &cube);
    this->moveMap["Y'"] = bind(&RubiksCubeModel::yPrime, &cube);
    this->moveMap["Y2"] = bind(&RubiksCubeModel::y2,     &cube);

    this->moveMap["Z"]  = bind(&RubiksCubeModel::z,      &cube);
    this->moveMap["Z'"] = bind(&RubiksCubeModel::zPrime, &cube);
    this->moveMap["Z2"] = bind(&RubiksCubeModel::z2,     &cube);
  }

  /**
   * Get a move map with the string representation of a move
   * to the corresponding move function in the cube passed
   * to the constructor.
   */
  MoveStore::moveFuncMap_t& ModelRotationStore::getMoveMap()
  {
    return this->moveMap;
  }

  /**
   * Constant version of the abolve.
   */
  const MoveStore::moveFuncMap_t& ModelRotationStore::getMoveMap() const
  {
    return this->moveMap;
  }
}

