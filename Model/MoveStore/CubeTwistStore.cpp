#include "CubeTwistStore.h"

namespace busybin
{
  /**
   * Init.
   * @param cube A RubiksCube reference for storing the move
   *        string->function map.
   */
  CubeTwistStore::CubeTwistStore(RubiksCubeWorldObject& cube)
  {
    // Set up the move map.
    this->moveMap["L"]  = bind(&RubiksCubeWorldObject::l,      &cube);
    this->moveMap["L'"] = bind(&RubiksCubeWorldObject::lPrime, &cube);
    this->moveMap["L2"] = bind(&RubiksCubeWorldObject::l2,     &cube);

    this->moveMap["R"]  = bind(&RubiksCubeWorldObject::r,      &cube);
    this->moveMap["R'"] = bind(&RubiksCubeWorldObject::rPrime, &cube);
    this->moveMap["R2"] = bind(&RubiksCubeWorldObject::r2,     &cube);

    this->moveMap["U"]  = bind(&RubiksCubeWorldObject::u,      &cube);
    this->moveMap["U'"] = bind(&RubiksCubeWorldObject::uPrime, &cube);
    this->moveMap["U2"] = bind(&RubiksCubeWorldObject::u2,     &cube);

    this->moveMap["D"]  = bind(&RubiksCubeWorldObject::d,      &cube);
    this->moveMap["D'"] = bind(&RubiksCubeWorldObject::dPrime, &cube);
    this->moveMap["D2"] = bind(&RubiksCubeWorldObject::d2,     &cube);

    this->moveMap["F"]  = bind(&RubiksCubeWorldObject::f,      &cube);
    this->moveMap["F'"] = bind(&RubiksCubeWorldObject::fPrime, &cube);
    this->moveMap["F2"] = bind(&RubiksCubeWorldObject::f2,     &cube);

    this->moveMap["B"]  = bind(&RubiksCubeWorldObject::b,      &cube);
    this->moveMap["B'"] = bind(&RubiksCubeWorldObject::bPrime, &cube);
    this->moveMap["B2"] = bind(&RubiksCubeWorldObject::b2,     &cube);
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

