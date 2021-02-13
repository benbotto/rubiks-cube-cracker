#ifndef _BUSYBIN_PATTERN_DATABASE_INDEXER_
#define _BUSYBIN_PATTERN_DATABASE_INDEXER_

#include "MovePruner.h"
#include "../../Model/RubiksCubeIndexModel.h"
#include "../../Model/Goal/Goal.h"
#include "../../Util/AutoTimer.h"
#include "../../Model/PatternDatabase/PatternDatabase.h"
#include <stack>
using std::stack;
#include <iostream>
using std::cout;
using std::endl;
#include <cstdint>

namespace busybin
{
  /**
   * Used to search the cube and index a pattern database.
   */
  class PatternDatabaseIndexer
  {
    struct Node
    {
      RubiksCubeIndexModel cube;
      uint8_t moveInd;
      uint8_t depth;
    };

  public:
    void findGoal(Goal& goal, RubiksCubeIndexModel& cube, PatternDatabase& seenDB);
  };
}

#endif

