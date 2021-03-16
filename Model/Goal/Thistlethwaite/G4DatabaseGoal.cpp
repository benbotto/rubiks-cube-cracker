#include "G4DatabaseGoal.h"

namespace busybin
{
  /**
   * Init, storing a pointer to the database.
   * @param pDatabase A pointer to a pattern database.
   */
  G4DatabaseGoal::G4DatabaseGoal(G4PatternDatabase* pDatabase) :
    DatabaseGoal(pDatabase)
  {
  }

  /**
   * Describe the goal.
   */
  string G4DatabaseGoal::getDescription() const
  {
    return "Create a database with the number of moves required to get to each state reachable with only half twists.";
  }
}
