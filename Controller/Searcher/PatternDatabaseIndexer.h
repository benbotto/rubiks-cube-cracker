#ifndef _BUSYBIN_PATTERN_DATABASE_INDEXER_
#define _BUSYBIN_PATTERN_DATABASE_INDEXER_

#include "CubeSearcher.h"
#include "../../Model/RubiksCubeModel.h"
#include "../../Model/Goal/Goal.h"
#include "../../Model/MoveStore/MoveStore.h"
#include "../../Util/AutoTimer.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <stack>
using std::stack;
#include <iostream>
using std::cout;
using std::endl;
#include <cstdint>

namespace busybin
{
  /**
   * A searcher that is specialized for indexing pattern databases.
   */
  class PatternDatabaseIndexer : public CubeSearcher
  {
    struct Node
    {
      RubiksCubeModel cube;
      uint8_t         moveInd;
      uint8_t         depth;
    };

  public:
    vector<string> findGoal(Goal& goal, RubiksCubeModel& cube, MoveStore& moveStore);
  };
}

#endif

