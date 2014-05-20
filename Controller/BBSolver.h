#ifndef _BUSYBIN_BB_SOLVER_H_
#define _BUSYBIN_BB_SOLVER_H_

#include "Evaluator.h"
#include "../Model/MoveStore.h"
#include "../Model/RubiksCube.h"
#include "../View/RubiksCubeView.h"
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <set>
using std::set;

namespace busybin
{
  /**
   * Branch and bound solver.
   */
  class BBSolver
  {
    RubiksCube* const pCube;
    MoveStore      moveStore;
    unsigned       maxDepth;
    Evaluator      evaluator;
    RubiksCubeView cubeView;

    unsigned max(unsigned depth, set<string>& cubeStates);
    string cubeToString() const;

  public:
    BBSolver(RubiksCube& cube);
    vector<string> solve();
  };
}

#endif

