#ifndef _BUSYBIN_DATABASE_GOAL_H_
#define _BUSYBIN_DATABASE_GOAL_H_

#include "Goal.h"
#include "../PatternDatabase/PatternDatabase.h"
#include <cstddef>
using std::size_t;

namespace busybin
{
  class DatabaseGoal : public Goal
  {
    PatternDatabase* pDatabase;

  public:
    DatabaseGoal(PatternDatabase* pDatabase);
    bool isSatisfied(RubiksCubeModel& cube);
    bool index(const RubiksCubeModel& cube, size_t numMoves);
  };
}

#endif

