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
  bool DatabaseGoal::isSatisfied(RubiksCube& cube)
  {
    return this->pDatabase->isFull();
  }

  /**
   * Index the cube.  Returns true if the state is indexed, false if the
   * state has been reached before (and therefore in fewer moves).
   * @param cube
   * @param numMoves The number of moves required to get to this cube state.
   */
  bool DatabaseGoal::index(const RubiksCube& cube, uint8_t numMoves)
  {
    return this->pDatabase->setNumMoves(cube, numMoves);
  }

  /**
   * Index the cube.  Returns true if the state is indexed, false if the
   * state has been reached before (and therefore in fewer moves).
   * @param ind An index into the database.
   * @param numMoves The number of moves required to get to this cube state.
   */
  bool DatabaseGoal::index(const uint32_t ind, uint8_t numMoves)
  {
    return this->pDatabase->setNumMoves(ind, numMoves);
  }

  /**
   * Get the number of moves to the cube state.
   * @param cube
   */
  uint8_t DatabaseGoal::getNumMoves(const RubiksCube& cube) const
  {
    return this->pDatabase->getNumMoves(cube);
  }

  /**
   * Get the number of moves using an index into the database.
   * @param ind The database index.
   */
  uint8_t DatabaseGoal::getNumMoves(const uint32_t ind) const
  {
    return this->pDatabase->getNumMoves(ind);
  }

  /**
   * Get the index for the cube (proxy to PatternDatabase#getDatabaseIndex).
   * @param cube
   */
  uint32_t DatabaseGoal::getDatabaseIndex(const RubiksCube& cube) const
  {
    return this->pDatabase->getDatabaseIndex(cube);
  }
}
