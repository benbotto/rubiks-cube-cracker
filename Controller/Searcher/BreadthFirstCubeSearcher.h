#ifndef _BUSYBIN_BREADTH_FIRST_CUBE_SEARCHER_H_
#define _BUSYBIN_BREADTH_FIRST_CUBE_SEARCHER_H_

#include "CubeSearcher.h"
#include "../../Model/RubiksCubeModel.h"
#include "../../Model/Goal/Goal.h"
#include "../../Model/MoveStore/MoveStore.h"
#include "../../Util/AutoTimer.h"
#include <vector>
using std::vector;
#include <queue>
using std::queue;
#include <string>
using std::string;
#include <cstdint>
#include <algorithm>
using std::reverse;

namespace busybin
{
  /**
   * A breadth first search implementation for the Rubik's Cube.
   */
  class BreadthFirstCubeSearcher : public CubeSearcher
  {
    struct node
    {
      uint16_t moveInd;
      node*    parent;
      uint8_t  depth;
    };

  public:
    vector<string> findGoal(Goal& goal, RubiksCubeModel& cube,
      MoveStore& moveStore);
  };
}

#endif

