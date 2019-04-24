#include "EdgeDatabaseGoal.h"

namespace busybin
{
  /**
   * Init, storing a pointer to the database.
   * @param pDatabase A pointer to a pattern database.
   */
  EdgeDatabaseGoal::EdgeDatabaseGoal(EdgePatternDatabase* pDatabase) :
    DatabaseGoal(pDatabase)
  {
  }

  /**
   * Describe the goal.
   */
  string EdgeDatabaseGoal::getDescription() const
  {
    return "Create a database of 6 of the 12 edge states.";
  }
}

