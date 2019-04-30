#include "ModelRotationStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCubeModel reference for storing the move
   *        string->function map.
   */
  ModelRotationStore::ModelRotationStore(RubiksCubeModel& cube) : pCube(&cube)
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

    this->moveInds[0] = RubiksCubeModel::MOVE::X;
    this->moveInds[1] = RubiksCubeModel::MOVE::XPRIME;
    this->moveInds[2] = RubiksCubeModel::MOVE::X2;
    this->moveInds[3] = RubiksCubeModel::MOVE::Y;
    this->moveInds[4] = RubiksCubeModel::MOVE::YPRIME;
    this->moveInds[5] = RubiksCubeModel::MOVE::Y2;
    this->moveInds[6] = RubiksCubeModel::MOVE::Z;
    this->moveInds[7] = RubiksCubeModel::MOVE::ZPRIME;
    this->moveInds[8] = RubiksCubeModel::MOVE::Z2;
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

  /**
   * Move using an index.
   */
  void ModelRotationStore::move(uint8_t ind)
  {
    this->pCube->move(this->moveInds.at(ind));
  }

  /**
   * Undo a move.
   */
  void ModelRotationStore::invert(uint8_t ind)
  {
    this->pCube->invert(this->moveInds.at(ind));
  }
}

