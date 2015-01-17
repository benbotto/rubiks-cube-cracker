#include "ModelG1TwistStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCubeModel reference for storing the move
   *        string->function map.
   */
  ModelG1TwistStore::ModelG1TwistStore(RubiksCubeModel& cube) :
    TwistStore(vector<string>({{"L", "R", "U2", "D2", "F", "B"}}))
  {
    // Set up the move map.
    this->moveMap["L"]  = bind(&RubiksCubeModel::l,      &cube);
    this->moveMap["L'"] = bind(&RubiksCubeModel::lPrime, &cube);

    this->moveMap["R"]  = bind(&RubiksCubeModel::r,      &cube);
    this->moveMap["R'"] = bind(&RubiksCubeModel::rPrime, &cube);

    this->moveMap["U2"] = bind(&RubiksCubeModel::u2,     &cube);

    this->moveMap["D2"] = bind(&RubiksCubeModel::d2,     &cube);

    this->moveMap["F"]  = bind(&RubiksCubeModel::f,      &cube);
    this->moveMap["F'"] = bind(&RubiksCubeModel::fPrime, &cube);

    this->moveMap["B"]  = bind(&RubiksCubeModel::b,      &cube);
    this->moveMap["B'"] = bind(&RubiksCubeModel::bPrime, &cube);
  }

  /**
   * Get a move map with the string representation of a move
   * to the corresponding move function in the cube passed
   * to the constructor.
   */
  MoveStore::moveFuncMap_t& ModelG1TwistStore::getMoveMap()
  {
    return this->moveMap;
  }

  /**
   * Constant version of the abolve.
   */
  const MoveStore::moveFuncMap_t& ModelG1TwistStore::getMoveMap() const
  {
    return this->moveMap;
  }
}

