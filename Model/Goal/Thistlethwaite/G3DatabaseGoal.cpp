#include "G3DatabaseGoal.h"

namespace busybin
{
  /**
   * Init, storing a pointer to the database.
   * @param pDatabase A pointer to a pattern database.
   */
  G3DatabaseGoal::G3DatabaseGoal(G3PatternDatabase* pDatabase) :
    DatabaseGoal(pDatabase)
  {
  }

  /**
   * Describe the goal.
   */
  string G3DatabaseGoal::getDescription() const
  {
    return "Create a database with the number of moves required to pair all corners in their tetrads and get all edges into their slices.";
  }
}
