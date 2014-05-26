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
  bool Goal1::isSatisfied(const RubiksCube& cube)
  {
    return
      cube.isSolved(RubiksCube::FACE::UP,    RubiksCube::FACE::LEFT)  ||
      cube.isSolved(RubiksCube::FACE::UP,    RubiksCube::FACE::FRONT) ||
      cube.isSolved(RubiksCube::FACE::UP,    RubiksCube::FACE::RIGHT) ||
      cube.isSolved(RubiksCube::FACE::UP,    RubiksCube::FACE::BACK)  ||
      cube.isSolved(RubiksCube::FACE::LEFT,  RubiksCube::FACE::FRONT) ||
      cube.isSolved(RubiksCube::FACE::FRONT, RubiksCube::FACE::RIGHT) ||
      cube.isSolved(RubiksCube::FACE::RIGHT, RubiksCube::FACE::BACK)  ||
      cube.isSolved(RubiksCube::FACE::LEFT,  RubiksCube::FACE::BACK)  ||
      cube.isSolved(RubiksCube::FACE::LEFT,  RubiksCube::FACE::DOWN)  ||
      cube.isSolved(RubiksCube::FACE::FRONT, RubiksCube::FACE::DOWN)  ||
      cube.isSolved(RubiksCube::FACE::RIGHT, RubiksCube::FACE::DOWN)  ||
      cube.isSolved(RubiksCube::FACE::BACK,  RubiksCube::FACE::DOWN);
  }
}
