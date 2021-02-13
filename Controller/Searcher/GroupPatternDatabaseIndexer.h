#ifndef _BUSYBIN_GROUP_PATTERN_DATABASE_INDEXER_
#define _BUSYBIN_GROUP_PATTERN_DATABASE_INDEXER_

#include "MovePruner.h"
#include "../../Model/RubiksCubeIndexModel.h"
#include "../../Model/Goal/Goal.h"
#include "../../Model/MoveStore/MoveStore.h"
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
   * Used to search the cube and index a pattern database.  This is similar to
   * the standard PatternDatabaseIndexer, but intended to build indexes for
   * groups, for example Thistlethwaite's groups.
   */
  class GroupPatternDatabaseIndexer
  {
    struct Node
    {
      RubiksCubeIndexModel cube;
      RubiksCube::MOVE move;
      uint8_t depth;
      uint8_t distanceToGroup;
    };

  public:
    void findGoal(Goal& goal, Goal& groupGoal,
      RubiksCubeIndexModel& solvedCube, PatternDatabase& seenDB,
      MoveStore& moveStore) const;
  };
}

#endif

