#include "TestGoal.h"

namespace busybin
{
  TestGoal::TestGoal(TestPatternDatabase* pDatabase) : DatabaseGoal(pDatabase)
  {
  }

  /**
   * Describe the goal.
   */
  string TestGoal::getDescription() const
  {
    return "Test goal for checking searchers.";
  }
}
