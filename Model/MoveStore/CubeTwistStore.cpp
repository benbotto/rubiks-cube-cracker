#include "CubeTwistStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCube reference for storing the move
   *        string->function map.
   */
  CubeTwistStore::CubeTwistStore(RubiksCube& cube)
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
  }

  /**
   * Get a move map with the string representation of a move
   * to the corresponding move function in the cube passed
   * to the constructor.
   */
  MoveStore::moveFuncMap_t& CubeTwistStore::getMoveMap()
  {
    return this->moveMap;
  }

  /**
   * Constant version of the above.
   */
  const MoveStore::moveFuncMap_t& CubeTwistStore::getMoveMap() const
  {
    return this->moveMap;
  }
}

