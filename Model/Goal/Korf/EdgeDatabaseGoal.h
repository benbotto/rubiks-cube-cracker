#ifndef _BUSYBIN_EDGE_DATABASE_GOAL_H_
#define _BUSYBIN_Edge_DATABASE_GOAL_H_

#include "../DatabaseGoal.h"
#include "../../PatternDatabase/EdgePatternDatabase.h"
#include <cstddef>
using std::size_t;

namespace busybin
{
  class EdgeDatabaseGoal : public DatabaseGoal
  {
  public:
    EdgeDatabaseGoal(EdgePatternDatabase* pDatabase);
    string getDescription() const;
  };
}

#endif
