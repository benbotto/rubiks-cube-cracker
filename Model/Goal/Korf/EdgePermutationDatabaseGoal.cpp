#include "EdgePermutationDatabaseGoal.h"

namespace busybin
{
  /**
   * Init, storing a pointer to the database.
   * @param pDatabase A pointer to a pattern database.
   */
  EdgePermutationDatabaseGoal::EdgePermutationDatabaseGoal(
    EdgePermutationPatternDatabase* pDatabase) :
    DatabaseGoal(pDatabase)
  {
  }

  /**
   * Describe the goal.
   */
  string EdgePermutationDatabaseGoal::getDescription() const
  {
    return "Create a database of the permutations of the 12 edge cubies.";
  }
}

