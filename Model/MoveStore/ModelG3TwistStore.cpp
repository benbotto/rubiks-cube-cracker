#include "ModelG3TwistStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCubeModel reference for storing the move
   *        string->function map.
   */
  ModelG3TwistStore::ModelG3TwistStore(RubiksCubeModel& cube) :
    TwistStore(vector<string>({{"L2", "R2", "U2", "D2", "F2", "B2"}})),
    pCube(&cube)
  {
    // Set up the move map.
    this->moveMap["L2"] = bind(&RubiksCubeModel::l2, &cube);
    this->moveMap["R2"] = bind(&RubiksCubeModel::r2, &cube);
    this->moveMap["U2"] = bind(&RubiksCubeModel::u2, &cube);
    this->moveMap["D2"] = bind(&RubiksCubeModel::d2, &cube);
    this->moveMap["F2"] = bind(&RubiksCubeModel::f2, &cube);
    this->moveMap["B2"] = bind(&RubiksCubeModel::b2, &cube);

    this->moveInds[0] = RubiksCubeModel::MOVE::L2;
    this->moveInds[1] = RubiksCubeModel::MOVE::R2;
    this->moveInds[2] = RubiksCubeModel::MOVE::U2;
    this->moveInds[3] = RubiksCubeModel::MOVE::D2;
    this->moveInds[4] = RubiksCubeModel::MOVE::F2;
    this->moveInds[5] = RubiksCubeModel::MOVE::B2;
  }

  /**
   * Get a move map with the string representation of a move
   * to the corresponding move function in the cube passed
   * to the constructor.
   */
  MoveStore::moveFuncMap_t& ModelG3TwistStore::getMoveMap()
  {
    return this->moveMap;
  }

  /**
   * Constant version of the abolve.
   */
  const MoveStore::moveFuncMap_t& ModelG3TwistStore::getMoveMap() const
  {
    return this->moveMap;
  }

  /**
   * Move using an index.
   */
  void ModelG3TwistStore::move(uint8_t ind)
  {
    this->pCube->move(this->moveInds.at(ind));
  }

  /**
   * Undo a move.
   */
  void ModelG3TwistStore::invert(uint8_t ind)
  {
    this->pCube->invert(this->moveInds.at(ind));
  }
}

