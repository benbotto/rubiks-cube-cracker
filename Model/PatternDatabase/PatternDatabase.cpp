#include "PatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the underlying array.
   */
  PatternDatabase::PatternDatabase(const size_t size) :
    database(size, 0xFF), size(size), numItems(0)
  {
  }

  /**
   * Set the number of moves to get to a scrambled cube state using an index.
   * The index should be calculated using the getDatabaseIndex method.  If the
   * state is already set, then this method does nothing and returns false.  If
   * the new state is indexed, then this method returns true.
   * @param ind The index in the database.
   * @param numMoves The number of moves to get to this state (must be fewer
   * than 15).
   */
  bool PatternDatabase::setNumMoves(const uint32_t ind, const uchar numMoves) 
  {
    if (this->getNumMoves(ind) == 0xF)
    {
      this->database.set(ind, numMoves);
      ++this->numItems;

      return true;
    }

    return false;
  }

  /**
   * Set the number of moves to get to a scrambled cube state.  The index is
   * calculated using the getDatabaseIndex method.
   * @param cube A cube instance.
   * @param numMoves The number of moves to get to this state (must be fewer
   * than 15).
   */
  bool PatternDatabase::setNumMoves(const RubiksCubeModel& cube, const uchar numMoves)
  {
    return this->setNumMoves(this->getDatabaseIndex(cube), numMoves);
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

  /**
   * Get the size of the database.
   */
  size_t PatternDatabase::getSize() const
  {
    return this->size;
  }

  /**
   * Get the number of items set in the database.
   */
  size_t PatternDatabase::getNumItems() const
  {
    return this->numItems;
  }

  /**
   * Returns true if every entry in the database has been added.
   */
  bool PatternDatabase::isFull() const
  {
    return this->numItems == this->size;
  }
}

