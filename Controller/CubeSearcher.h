#ifndef _BUSYBIN_CUBE_SEARCHER_H_
#define _BUSYBIN_CUBE_SEARCHER_H_

#include "../Model/RubiksCubeModel.h"
#include "../Model/Goal/Goal.h"
#include "../Model/MoveStore.h"
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
    MoveStore moveStore;

    bool find(Goal& goal, unsigned depth, unsigned maxDepth,
      vector<string>& moves);

  public:
    CubeSearcher(RubiksCubeModel& cube);
    vector<string> find(Goal& goal, vector<string>& moves);
  };
}

#endif

