#include "CornerDatabaseGoal.h"

namespace busybin
{
  /**
   * Init, storing a pointer to the database.
   * @param pDatabase A pointer to a pattern database.
   */
  CornerDatabaseGoal::CornerDatabaseGoal(CornerPatternDatabase* pDatabase) :
    DatabaseGoal(pDatabase)
  {
  }

  /**
   * Describe the goal.
   */
  string CornerDatabaseGoal::getDescription() const
  {
    return "Create a database of all corner states.";
  }
}

