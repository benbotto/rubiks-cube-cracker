#ifndef _BUSYBIN_PATTERN_DATABASE_INDEXER_
#define _BUSYBIN_PATTERN_DATABASE_INDEXER_

#include "MovePruner.h"
#include "../../Model/RubiksCube.h"
#include "../../Model/RubiksCubeIndexModel.h"
#include "../../Model/Goal/DatabaseGoal.h"
#include "../../Model/MoveStore/MoveStore.h"
#include "../../Util/AutoTimer.h"
#include <stack>
using std::stack;
#include <iostream>
using std::cout;
using std::endl;
#include <cstdint>

namespace busybin
{
  /**
   * Used to search the cube and index a pattern database using a DatabaseGoal.
   */
  class PatternDatabaseIndexer
  {
    struct Node
    {
      RubiksCubeIndexModel cube;
      RubiksCube::MOVE move;
      uint8_t depth;
    };

  public:
    void findGoal(DatabaseGoal& goal, RubiksCubeIndexModel& cube,
      MoveStore& moveStore);
  };
}

#endif

