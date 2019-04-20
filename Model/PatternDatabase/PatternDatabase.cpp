#include "PatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the underlying array.
   */
  PatternDatabase::PatternDatabase(const size_t size) : database(size, 0xFF)
  {
  }

  /**
   * Set the number of moves to get to a scrambled cube state using an index.
   * The index should be calculated using the getDatabaseIndex method.  If
   * the state is already set, then this method does nothing.
   * @param ind The index in the database.
   * @param numMoves The number of moves to get to this state (must be fewer
   * than 15).
   */
  void PatternDatabase::setNumMoves(const uint32_t ind, const uchar numMoves) 
  {
    if (this->getNumMoves(ind) == 0xF)
      this->database.set(ind, numMoves);
  }

  /**
   * Set the number of moves to get to a scrambled cube state.  The index is
   * calculated using the getDatabaseIndex method.
   * @param cube A cube instance.
   * @param numMoves The number of moves to get to this state (must be fewer
   * than 15).
   */
  void PatternDatabase::setNumMoves(const RubiksCubeModel& cube, const uchar numMoves)
  {
    this->setNumMoves(this->getDatabaseIndex(cube), numMoves);
  }

  /**
   * Get the number of moves it takes to get to a scrambled cube state using
   * and index.  The index should be calculated using the getDatabaseIndex
   * method.  0xF (15) indicates that the state has not been set.
   * @param cube A cube instance.
   */
  unsigned char PatternDatabase::getNumMoves(const uint32_t ind) const
  {
    return this->database.get(ind);
  }

  /**
   * Get the number of moves it takes to get to a scrambled cube.  The index is
   * calculated using the getDatabaseIndex method.  0xF indicates that the
   * state has not been set.
   * @param cube A cube instance.
   */
  unsigned char PatternDatabase::getNumMoves(const RubiksCubeModel& cube) const
  {
    return this->getNumMoves(this->getDatabaseIndex(cube));
  }
}

