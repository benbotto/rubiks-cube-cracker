#ifndef _BUSYBIN_CORNER_DATABASE_GOAL_H_
#define _BUSYBIN_CORNER_DATABASE_GOAL_H_

#include "../DatabaseGoal.h"
#include "../../PatternDatabase/Korf/CornerPatternDatabase.h"
#include <cstddef>
using std::size_t;

namespace busybin
{
  class CornerDatabaseGoal : public DatabaseGoal
  {
  public:
    CornerDatabaseGoal(CornerPatternDatabase* pDatabase);
    string getDescription() const;
  };
}

#endif

