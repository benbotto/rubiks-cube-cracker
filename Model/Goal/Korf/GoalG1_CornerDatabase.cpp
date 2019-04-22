#include "GoalG1_CornerDatabase.h"

namespace busybin
{
  /**
   * Init, storing a pointer to the database.
   * @param pDatabase A pointer to a pattern database.
   */
  GoalG1_CornerDatabase::GoalG1_CornerDatabase(CornerPatternDatabase* pDatabase) :
    DatabaseGoal(pDatabase)
  {
  }

  /**
   * Describe the goal.
   */
  string GoalG1_CornerDatabase::getDescription() const
  {
    return "Create a database of all corner states.";
  }
}

