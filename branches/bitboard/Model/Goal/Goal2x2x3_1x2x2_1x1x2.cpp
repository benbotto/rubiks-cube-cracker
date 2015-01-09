#include "Goal2x2x3_1x2x2_1x1x2.h"

namespace busybin
{
  /**
   * Solve a 2x2x3 and 1x2x2, and put a 1x1x2 together.
   * @param cube The cube.
   */
  bool Goal2x2x3_1x2x2_1x1x2::isSatisfied(RubiksCubeModel& cube)
  {
    typedef RubiksCubeModel::FACE        F;
    typedef RubiksCubeModel::CenterCubie CenterCubie;
    typedef RubiksCubeModel::CornerCubie CornerCubie;
    typedef RubiksCubeModel::EdgeCubie   EdgeCubie;

    this->updateSolved(cube);

    // The color of the bottom.
    CenterCubie cD = cube.getCubie(F::DOWN);

    // The remaining unsolved corners.
    CornerCubie cLUB = cube.getCubie(F::LEFT,  F::UP,   F::BACK);
    CornerCubie cLUF = cube.getCubie(F::LEFT,  F::UP,   F::FRONT);
    CornerCubie cRUB = cube.getCubie(F::RIGHT, F::UP,   F::BACK);
    CornerCubie cRUF = cube.getCubie(F::RIGHT, F::UP,   F::FRONT);
    CornerCubie cLDF = cube.getCubie(F::LEFT,  F::DOWN, F::FRONT);

    // The remaining unsolved edges.
    EdgeCubie cLU  = cube.getCubie(F::LEFT,  F::UP);
    EdgeCubie cUF  = cube.getCubie(F::UP,    F::FRONT);
    EdgeCubie cUB  = cube.getCubie(F::UP,    F::BACK);
    EdgeCubie cRU  = cube.getCubie(F::RIGHT, F::UP);
    EdgeCubie cLF  = cube.getCubie(F::LEFT,  F::FRONT);

    return
      // 2x2x3 solved and oriented in the bottom back.
      this->LD && this->LDB && this->DB && this->RDB && this->RD && this->LB && this->RB &&
      // 1x2x2 in the front right.
      this->DF && this->RDF && this->RF &&
      (
        // 1x1x2 matched in the left, up, back (2 cases).
        (cD == cLUB[0] && cLUB[1] == cUB[0] && cLUB[2] == cUB[1]) ||
        (cD == cLUB[2] && cLUB[1] == cLU[1] && cLUB[0] == cLU[0]) ||

        // 1x1x2 matched in the right, up, back (2 cases).
        (cD == cRUB[0] && cRUB[1] == cUB[0] && cRUB[2] == cUB[1]) ||
        (cD == cRUB[2] && cRUB[1] == cRU[1] && cRUB[0] == cRU[0]) ||

        // 1x1x2 matched in the left, up, front (3 cases).
        (cD == cLUF[0] && cLUF[1] == cUF[0] && cLUF[2] == cUF[1]) ||
        (cD == cLUF[2] && cLUF[1] == cLU[1] && cLUF[0] == cLU[0]) ||
        (cD == cLUF[1] && cLUF[2] == cLF[1] && cLUF[0] == cLF[0]) ||

        // 1x1x2 matched in the right, up, front (2 cases).
        (cD == cRUF[0] && cRUF[1] == cUF[0] && cRUF[2] == cUF[1]) ||
        (cD == cRUF[2] && cRUF[1] == cRU[1] && cRUF[0] == cRU[0]) ||

        // 1x1x2 matched in the left, down, front (1 case).
        (cD == cLDF[1] && cLDF[2] == cLF[1] && cLDF[0] == cLF[0])
      );
  }

  /**
   * Describe the goal.
   */
  string Goal2x2x3_1x2x2_1x1x2::getDescription() const
  {
    return "Solve a 2x2x3 and 1x2x2, and put a 1x1x2 together.";
  }
}

