#include "TestGoal.h"

namespace busybin
{
  /**
   * Test goal for testing searchers.
   * @param cube The cube.
   */
  bool TestGoal::isSatisfied(RubiksCube& cube)
  {
    RubiksCubeModel& cubeModel = static_cast<RubiksCubeModel&>(cube);

    // Reachable using F U R U' R' F'.
    return
      cubeModel.getFace(FACE::FRONT) == 0x000000000030200 &&
      cubeModel.getFace(FACE::RIGHT) == 0x101010101050500 &&
      cubeModel.getFace(FACE::UP)    == 0x201010202020001 &&
      cubeModel.getFace(FACE::LEFT)  == 0x303030303020302 &&
      cubeModel.getFace(FACE::DOWN)  == 0x404040404040404 &&
      cubeModel.getFace(FACE::BACK)  == 0x505050505050203;
  }

  /**
   * Describe the goal.
   */
  string TestGoal::getDescription() const
  {
    return "Test goal for checking searchers.";
  }
}
