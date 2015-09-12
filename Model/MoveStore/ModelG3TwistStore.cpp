#include "ModelG3TwistStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCubeModel reference for storing the move
   *        string->function map.
   */
  ModelG3TwistStore::ModelG3TwistStore(RubiksCubeModel& cube) :
    TwistStore(vector<string>({{"L2", "R2", "U2", "D2", "F2", "B2"}}))
  {
    // Set up the move map.
    this->moveMap["L2"] = bind(&RubiksCubeModel::l2, &cube);
    this->moveMap["R2"] = bind(&RubiksCubeModel::r2, &cube);
    this->moveMap["U2"] = bind(&RubiksCubeModel::u2, &cube);
    this->moveMap["D2"] = bind(&RubiksCubeModel::d2, &cube);
    this->moveMap["F2"] = bind(&RubiksCubeModel::f2, &cube);
    this->moveMap["B2"] = bind(&RubiksCubeModel::b2, &cube);
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
}

