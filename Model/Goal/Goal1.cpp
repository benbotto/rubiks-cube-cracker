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
    return
      cube.isSolved(RubiksCubeModel::FACE::UP,    RubiksCubeModel::FACE::LEFT)  ||
      cube.isSolved(RubiksCubeModel::FACE::UP,    RubiksCubeModel::FACE::FRONT) ||
      cube.isSolved(RubiksCubeModel::FACE::UP,    RubiksCubeModel::FACE::RIGHT) ||
      cube.isSolved(RubiksCubeModel::FACE::UP,    RubiksCubeModel::FACE::BACK)  ||
      cube.isSolved(RubiksCubeModel::FACE::LEFT,  RubiksCubeModel::FACE::FRONT) ||
      cube.isSolved(RubiksCubeModel::FACE::FRONT, RubiksCubeModel::FACE::RIGHT) ||
      cube.isSolved(RubiksCubeModel::FACE::RIGHT, RubiksCubeModel::FACE::BACK)  ||
      cube.isSolved(RubiksCubeModel::FACE::LEFT,  RubiksCubeModel::FACE::BACK)  ||
      cube.isSolved(RubiksCubeModel::FACE::LEFT,  RubiksCubeModel::FACE::DOWN)  ||
      cube.isSolved(RubiksCubeModel::FACE::FRONT, RubiksCubeModel::FACE::DOWN)  ||
      cube.isSolved(RubiksCubeModel::FACE::RIGHT, RubiksCubeModel::FACE::DOWN)  ||
      cube.isSolved(RubiksCubeModel::FACE::BACK,  RubiksCubeModel::FACE::DOWN);
  }
}
