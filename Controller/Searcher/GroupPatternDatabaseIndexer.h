#ifndef _BUSYBIN_GROUP_PATTERN_DATABASE_INDEXER_
#define _BUSYBIN_GROUP_PATTERN_DATABASE_INDEXER_

#include "MovePruner.h"
#include "../../Model/RubiksCubeIndexModel.h"
#include "../../Model/Goal/Goal.h"
#include "../../Model/Goal/DatabaseGoal.h"
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
    typedef RubiksCube::MOVE MOVE;

    unsigned findGoal(
      DatabaseGoal& goal,
      Goal& groupGoal,
      RubiksCubeIndexModel& cube,
      PatternDatabase& seenDB,
      MoveStore& moveStore,
      const unsigned bound,
      unsigned curDepth,
      const MOVE lastMove,
      const unsigned parentDist,
      bool& solved
    ) const;

  public:
    void findGoal(
      DatabaseGoal& goal,
      Goal& groupGoal,
      RubiksCubeIndexModel& cube,
      PatternDatabase& seenDB,
      MoveStore& moveStore
    ) const;
  };
}

#endif

