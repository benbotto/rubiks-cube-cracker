#include "OrientationDatabaseGoal.h"

namespace busybin
{
  /**
   * Init, storing a pointer to the database.
   * @param pDatabase A pointer to a pattern database.
   */
  OrientationDatabaseGoal::OrientationDatabaseGoal(OrientationPatternDatabase* pDatabase) :
    DatabaseGoal(pDatabase)
  {
  }

  /**
   * Describe the goal.
   */
  string OrientationDatabaseGoal::getDescription() const
  {
    return "Create a database of the orientations of all 20 cubies.";
  }
}

