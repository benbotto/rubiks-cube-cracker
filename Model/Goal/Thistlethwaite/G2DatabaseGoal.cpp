#include "G2DatabaseGoal.h"

namespace busybin
{
  /**
   * Init, storing a pointer to the database.
   * @param pDatabase A pointer to a pattern database.
   */
  G2DatabaseGoal::G2DatabaseGoal(G2PatternDatabase* pDatabase) :
    DatabaseGoal(pDatabase)
  {
  }

  /**
   * Describe the goal.
   */
  string G2DatabaseGoal::getDescription() const
  {
    return "Create a database with the number of moves to orient all corners and position the E-slice edges.";
  }
}

