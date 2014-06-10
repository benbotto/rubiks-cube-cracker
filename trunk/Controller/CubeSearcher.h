#ifndef _BUSYBIN_CUBE_SEARCHER_H_
#define _BUSYBIN_CUBE_SEARCHER_H_

#include "../Model/RubiksCubeModel.h"
#include "../Model/Goal/Goal.h"
#include "../Model/MoveStore/MoveStore.h"
#include "../Util/AutoTimer.h"
#include <vector>
using std::vector;
#include <string>
using std::string;

namespace busybin
{
  /**
   * Iterative deepening search for the cube.
   */
  class CubeSearcher
  {
    RubiksCubeModel* const pCube;
    MoveStore*       pMoveStore;

    bool findGoal(Goal& goal, unsigned depth, unsigned maxDepth,
      vector<string>& moves);
    bool findOrientation(Goal& goal, unsigned depth, unsigned maxDepth,
      vector<string>& moves);
  public:
    CubeSearcher(RubiksCubeModel& cube, MoveStore& moveStore);
    vector<string> findGoal(Goal& goal);
    vector<string> findOrientation(Goal& goal);
  };
}

#endif

