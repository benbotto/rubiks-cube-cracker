#include "Goal8.h"

namespace busybin
{
  /**
   * Solve 2 layers except for one corner/edge.  At least 10 edges solved.
   * @param cube The cube.
   */
  bool Goal8::isSatisfied(RubiksCubeModel& cube)
  {
    typedef RubiksCubeModel::FACE F;

    unsigned numSolvedEdges = 0;

    if (cube.isSolved(F::LEFT,  F::UP))    ++numSolvedEdges;
    if (cube.isSolved(F::LEFT,  F::FRONT)) ++numSolvedEdges;
    if (cube.isSolved(F::LEFT,  F::BACK))  ++numSolvedEdges;
    if (cube.isSolved(F::LEFT,  F::DOWN))  ++numSolvedEdges;
    if (cube.isSolved(F::DOWN,  F::FRONT)) ++numSolvedEdges;
    if (cube.isSolved(F::DOWN,  F::BACK))  ++numSolvedEdges;
    if (cube.isSolved(F::UP,    F::FRONT)) ++numSolvedEdges;
    if (cube.isSolved(F::UP,    F::BACK))  ++numSolvedEdges;
    if (cube.isSolved(F::RIGHT, F::UP))    ++numSolvedEdges;
    if (cube.isSolved(F::RIGHT, F::FRONT)) ++numSolvedEdges;
    if (cube.isSolved(F::RIGHT, F::BACK))  ++numSolvedEdges;
    if (cube.isSolved(F::RIGHT, F::DOWN))  ++numSolvedEdges;

    return this->goal7.isSatisfied(cube) && numSolvedEdges >= 10;
  }
}
