#ifndef _BUSYBIN_GOAL_G1_CORNER_DATABASE_H_
#define _BUSYBIN_GOAL_G1_CORNER_DATABASE_H_

#include "../DatabaseGoal.h"
#include "../../PatternDatabase/CornerPatternDatabase.h"
#include <cstddef>
using std::size_t;

namespace busybin
{
  class GoalG1_CornerDatabase : public DatabaseGoal
  {
  public:
    GoalG1_CornerDatabase(CornerPatternDatabase* pDatabase);
    string getDescription() const;
  };
}

#endif

