#include "Goal2x3x3_OE.h"

namespace busybin
{
  /**
   * Store the number of edges to orient.
   * @param numToOrient Number of top edges to orient.
   */
  Goal2x3x3_OE::Goal2x3x3_OE(unsigned numToOrient)
  {
    this->numToOrient = numToOrient;
  }

  /**
   * Solve a 2x3x3 and orient edges.
   * @param cube The cube.
   */
  bool Goal2x3x3_OE::isSatisfied(RubiksCubeModel& cube)
  {
    typedef RubiksCubeModel::FACE        F;
    typedef RubiksCubeModel::CenterCubie CenterCubie;
    typedef RubiksCubeModel::EdgeCubie   EdgeCubie;

    // The color of the top.
    CenterCubie cU = cube.getCubie(F::UP);

    // The top edges.
    unsigned orientedEdges = 0;

    EdgeCubie cUL = cube.getCubie(F::UP, F::LEFT);
    EdgeCubie cUF = cube.getCubie(F::UP, F::FRONT);
    EdgeCubie cUB = cube.getCubie(F::UP, F::BACK);
    EdgeCubie cUR = cube.getCubie(F::UP, F::RIGHT);

    if (cU == cUL[0]) ++orientedEdges;
    if (cU == cUF[0]) ++orientedEdges;
    if (cU == cUB[0]) ++orientedEdges;
    if (cU == cUR[0]) ++orientedEdges;

    // At least two edges must be oriented.
    if (orientedEdges < this->numToOrient)
      return false;

    return this->goal2x3x3.isSatisfied(cube);
  }

  /**
   * Describe the goal.
   */
  string Goal2x3x3_OE::getDescription() const
  {
    ostringstream desc;

    desc <<"Solve a 2x3x3 and orient " << this->numToOrient << " edges.";
    return desc.str();
  }
}

