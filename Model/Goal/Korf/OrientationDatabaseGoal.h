#ifndef _BUSYBIN_ORIENTATION_DATABASE_GOAL_H_
#define _BUSYBIN_ORIENTATION_DATABASE_GOAL_H_

#include "../DatabaseGoal.h"
#include "../../PatternDatabase/Korf/OrientationPatternDatabase.h"
#include <cstddef>
using std::size_t;

namespace busybin
{
  class OrientationDatabaseGoal : public DatabaseGoal
  {
  public:
    OrientationDatabaseGoal(OrientationPatternDatabase* pDatabase);
    string getDescription() const;
  };
}

#endif
