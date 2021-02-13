#ifndef _BUSYBIN_G1_DATABASE_GOAL_H_
#define _BUSYBIN_G1_DATABASE_GOAL_H_

#include "../DatabaseGoal.h"
#include "../../PatternDatabase/Thistlethwaite/G1PatternDatabase.h"

namespace busybin
{
  class G1DatabaseGoal : public DatabaseGoal
  {
  public:
    G1DatabaseGoal(G1PatternDatabase* pDatabase);
    string getDescription() const;
  };
}

#endif

