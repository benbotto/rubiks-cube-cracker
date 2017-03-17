#include "ModelG2TwistStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCubeModel reference for storing the move
   *        string->function map.
   */
  ModelG2TwistStore::ModelG2TwistStore(RubiksCubeModel& cube) :
    TwistStore(vector<string>({{"L", "R", "U2", "D2", "F2", "B2"}}))
  {
    // Set up the move map.
    this->moveMap["L"]  = bind(&RubiksCubeModel::l,      &cube);
    this->moveMap["L'"] = bind(&RubiksCubeModel::lPrime, &cube);
    this->moveMap["L2"] = bind(&RubiksCubeModel::l2,     &cube);
    this->moveMap["R"]  = bind(&RubiksCubeModel::r,      &cube);
    this->moveMap["R'"] = bind(&RubiksCubeModel::rPrime, &cube);
    this->moveMap["R2"] = bind(&RubiksCubeModel::r2,     &cube);
    this->moveMap["U2"] = bind(&RubiksCubeModel::u2,     &cube);
    this->moveMap["D2"] = bind(&RubiksCubeModel::d2,     &cube);
    this->moveMap["F2"] = bind(&RubiksCubeModel::f2,     &cube);
    this->moveMap["B2"] = bind(&RubiksCubeModel::b2,     &cube);
  }

  /**
   * Get a move map with the string representation of a move
   * to the corresponding move function in the cube passed
   * to the constructor.
   */
  MoveStore::moveFuncMap_t& ModelG2TwistStore::getMoveMap()
  {
    return this->moveMap;
  }

  /**
   * Constant version of the abolve.
   */
  const MoveStore::moveFuncMap_t& ModelG2TwistStore::getMoveMap() const
  {
    return this->moveMap;
  }
}

