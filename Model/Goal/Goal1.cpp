#include "Goal1.h"

namespace busybin
{
  /**
   * Init.
   */
  Goal1::Goal1()
  {
  }

  /**
   * Check if any edge is solved.
   * @param cube The cube.
   */
  bool Goal1::isSatisfied(const RubiksCubeModel& cube)
  {
    typedef RubiksCubeModel::FACE F;

    return
      cube.isSolved(F::UP,    F::LEFT)  ||
      cube.isSolved(F::UP,    F::FRONT) ||
      cube.isSolved(F::UP,    F::RIGHT) ||
      cube.isSolved(F::UP,    F::BACK)  ||
      cube.isSolved(F::LEFT,  F::FRONT) ||
      cube.isSolved(F::FRONT, F::RIGHT) ||
      cube.isSolved(F::RIGHT, F::BACK)  ||
      cube.isSolved(F::LEFT,  F::BACK)  ||
      cube.isSolved(F::LEFT,  F::DOWN)  ||
      cube.isSolved(F::FRONT, F::DOWN)  ||
      cube.isSolved(F::RIGHT, F::DOWN)  ||
      cube.isSolved(F::BACK,  F::DOWN);
  }
}
