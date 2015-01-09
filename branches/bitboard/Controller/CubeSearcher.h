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
    bool findGoal(Goal& goal, RubiksCubeModel& cube, MoveStore& moveStore,
      unsigned depth, unsigned maxDepth, vector<string>& moves);
    bool prune(const string& move, const MoveStore& moveStore, const vector<string>& moves) const;

  public:
    vector<string> findGoal(Goal& goal, RubiksCubeModel& cube, MoveStore& moveStore);
  };
}

#endif

