#include "ModelMoveStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCubeModel reference for storing the move
   *        string->function map.
   */
  ModelMoveStore::ModelMoveStore(RubiksCubeModel& cube)
  {
    // Set up the move map.
    this->moveMap["L"]  = bind(&RubiksCubeModel::l,      &cube);
    this->moveMap["L'"] = bind(&RubiksCubeModel::lPrime, &cube);
    this->moveMap["L2"] = bind(&RubiksCubeModel::l2,     &cube);

    this->moveMap["R"]  = bind(&RubiksCubeModel::r,      &cube);
    this->moveMap["R'"] = bind(&RubiksCubeModel::rPrime, &cube);
    this->moveMap["R2"] = bind(&RubiksCubeModel::r2,     &cube);

    this->moveMap["U"]  = bind(&RubiksCubeModel::u,      &cube);
    this->moveMap["U'"] = bind(&RubiksCubeModel::uPrime, &cube);
    this->moveMap["U2"] = bind(&RubiksCubeModel::u2,     &cube);

    this->moveMap["D"]  = bind(&RubiksCubeModel::d,      &cube);
    this->moveMap["D'"] = bind(&RubiksCubeModel::dPrime, &cube);
    this->moveMap["D2"] = bind(&RubiksCubeModel::d2,     &cube);

    this->moveMap["F"]  = bind(&RubiksCubeModel::f,      &cube);
    this->moveMap["F'"] = bind(&RubiksCubeModel::fPrime, &cube);
    this->moveMap["F2"] = bind(&RubiksCubeModel::f2,     &cube);

    this->moveMap["B"]  = bind(&RubiksCubeModel::b,      &cube);
    this->moveMap["B'"] = bind(&RubiksCubeModel::bPrime, &cube);
    this->moveMap["B2"] = bind(&RubiksCubeModel::b2,     &cube);

    // Set up the rotation map.
    this->rotMap["X"]  = bind(&RubiksCubeModel::x,      &cube);
    this->rotMap["X'"] = bind(&RubiksCubeModel::xPrime, &cube);
    this->rotMap["X2"] = bind(&RubiksCubeModel::x2,     &cube);

    this->rotMap["Y"]  = bind(&RubiksCubeModel::y,      &cube);
    this->rotMap["Y'"] = bind(&RubiksCubeModel::yPrime, &cube);
    this->rotMap["Y2"] = bind(&RubiksCubeModel::y2,     &cube);

    this->rotMap["Z"]  = bind(&RubiksCubeModel::z,      &cube);
    this->rotMap["Z'"] = bind(&RubiksCubeModel::zPrime, &cube);
    this->rotMap["Z2"] = bind(&RubiksCubeModel::z2,     &cube);
  }

  /**
   * Get a move map with the string representation of a move
   * to the corresponding move function in the cube passed
   * to the constructor.
   */
  MoveStore::moveMap_t& ModelMoveStore::getMoveMap()
  {
    return this->moveMap;
  }

  /**
   * Constant version of the abolve.
   */
  const MoveStore::moveMap_t& ModelMoveStore::getMoveMap() const
  {
    return this->moveMap;
  }

  /**
   * Get a rotation map with the string representation of a rotation
   * to the corresponding rotation function in the cube passed
   * to the constructor.
   */
  MoveStore::rotMap_t& ModelMoveStore::getRotationMap()
  {
    return this->rotMap;
  }

  /**
   * Constant version of the abolve.
   */
  const MoveStore::rotMap_t& ModelMoveStore::getRotationMap() const
  {
    return this->rotMap;
  }
}

