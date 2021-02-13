#include "G1DatabaseGoal.h"

namespace busybin
{
  /**
   * Init, storing a pointer to the database.
   * @param pDatabase A pointer to a pattern database.
   */
  G1DatabaseGoal::G1DatabaseGoal(G1PatternDatabase* pDatabase) :
    DatabaseGoal(pDatabase)
  {
  }

  /**
   * Describe the goal.
   */
  string G1DatabaseGoal::getDescription() const
  {
    return "Create a database with the number of moves from each edge orientation permutation to G1.";
  }
}

