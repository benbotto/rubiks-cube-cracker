#ifndef _BUSYBIN_IDDFS_CUBE_SEARCHER_H_
#define _BUSYBIN_IDDFS_CUBE_SEARCHER_H_

#include "CubeSearcher.h"
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
   * Iterative deepening depth-first searcher for the cube.
   */
  class IDDFSCubeSearcher : public CubeSearcher
  {
    bool findGoal(Goal& goal, RubiksCubeModel& cube, MoveStore& moveStore,
      unsigned depth, unsigned maxDepth, vector<string>& moves);

  public:
    vector<string> findGoal(Goal& goal, RubiksCubeModel& cube, MoveStore& moveStore);
  };
}

#endif

