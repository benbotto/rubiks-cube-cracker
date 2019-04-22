#include "DatabaseGoal.h"

namespace busybin
{
  /**
   * Init, storing a pointer to the database.
   * @param pDatabase A pointer to a pattern database.
   */
  DatabaseGoal::DatabaseGoal(PatternDatabase* pDatabase) :
    Goal(), pDatabase(pDatabase)
  {
  }

  /**
   * Check if the goal is satisfied (the database is full).
   */
  bool DatabaseGoal::isSatisfied(RubiksCubeModel& cube)
  {
    return this->pDatabase->isFull();
  }

  /**
   * Index the cube.  Returns true if the state is indexed, false if the
   * state has been reached before (and therefore in fewer moves).
   * @param cube
   * @param numMoves The number of moves required to get to this cube state.
   */
  bool DatabaseGoal::index(const RubiksCubeModel& cube, size_t numMoves)
  {
    return this->pDatabase->setNumMoves(cube, numMoves);
  }
}

