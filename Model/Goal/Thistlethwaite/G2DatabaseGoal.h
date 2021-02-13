#ifndef _BUSYBIN_G2_DATABASE_GOAL_H_
#define _BUSYBIN_G2_DATABASE_GOAL_H_

#include "../DatabaseGoal.h"
#include "../../PatternDatabase/Thistlethwaite/G2PatternDatabase.h"

namespace busybin
{
  class G2DatabaseGoal : public DatabaseGoal
  {
  public:
    G2DatabaseGoal(G2PatternDatabase* pDatabase);
    string getDescription() const;
  };
}

#endif

