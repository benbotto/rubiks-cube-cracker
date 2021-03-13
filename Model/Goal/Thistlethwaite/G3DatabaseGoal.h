#ifndef _BUSYBIN_G3_DATABASE_GOAL_H_
#define _BUSYBIN_G3_DATABASE_GOAL_H_

#include "../DatabaseGoal.h"
#include "../../PatternDatabase/Thistlethwaite/G3PatternDatabase.h"

namespace busybin
{
  class G3DatabaseGoal : public DatabaseGoal
  {
  public:
    G3DatabaseGoal(G3PatternDatabase* pDatabase);
    string getDescription() const;
  };
}

#endif
