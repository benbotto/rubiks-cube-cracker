#ifndef _BUSYBIN_G4_DATABASE_GOAL_H_
#define _BUSYBIN_G4_DATABASE_GOAL_H_

#include "../DatabaseGoal.h"
#include "../../PatternDatabase/Thistlethwaite/G4PatternDatabase.h"

namespace busybin
{
  class G4DatabaseGoal : public DatabaseGoal
  {
  public:
    G4DatabaseGoal(G4PatternDatabase* pDatabase);
    string getDescription() const;
  };
}

#endif
