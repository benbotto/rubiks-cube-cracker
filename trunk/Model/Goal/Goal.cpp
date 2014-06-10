#include "Goal.h"

namespace busybin
{
  /**
   * Update the solved status of all cubies.
   * @param cube The cube.
   */
  void Goal::updateSolved(const RubiksCubeModel& cube)
  {
    typedef RubiksCubeModel::FACE F;

    this->LUF = cube.isSolved(F::LEFT,  F::UP,   F::FRONT);
    this->LUB = cube.isSolved(F::LEFT,  F::UP,   F::BACK);
    this->LDF = cube.isSolved(F::LEFT,  F::DOWN, F::FRONT);
    this->LDB = cube.isSolved(F::LEFT,  F::DOWN, F::BACK);
    this->RUF = cube.isSolved(F::RIGHT, F::UP,   F::FRONT);
    this->RUB = cube.isSolved(F::RIGHT, F::UP,   F::BACK);
    this->RDF = cube.isSolved(F::RIGHT, F::DOWN, F::FRONT);
    this->RDB = cube.isSolved(F::RIGHT, F::DOWN, F::BACK);
    this->LU  = cube.isSolved(F::LEFT,  F::UP);
    this->LF  = cube.isSolved(F::LEFT,  F::FRONT);
    this->LB  = cube.isSolved(F::LEFT,  F::BACK);
    this->LD  = cube.isSolved(F::LEFT,  F::DOWN);
    this->DF  = cube.isSolved(F::DOWN,  F::FRONT);
    this->DB  = cube.isSolved(F::DOWN,  F::BACK);
    this->UF  = cube.isSolved(F::UP,    F::FRONT);
    this->UB  = cube.isSolved(F::UP,    F::BACK);
    this->RU  = cube.isSolved(F::RIGHT, F::UP);
    this->RF  = cube.isSolved(F::RIGHT, F::FRONT);
    this->RB  = cube.isSolved(F::RIGHT, F::BACK);
    this->RD  = cube.isSolved(F::RIGHT, F::DOWN);
  }

  /**
   * Check if the cube is oriented correctly.
   */
  bool Goal::isOriented(RubiksCubeModel& cube) // TODO: remove
  {
    return true;
  }
}

