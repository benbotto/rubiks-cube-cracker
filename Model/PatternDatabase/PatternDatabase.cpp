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
  bool PatternDatabase::setNumMoves(const uint32_t ind, const uint8_t numMoves) 
  {
    uint8_t oldNumMoves = this->getNumMoves(ind);

    if (oldNumMoves == 0xF)
      ++this->numItems;

    if (oldNumMoves > numMoves)
    {
      this->database.set(ind, numMoves);
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
  bool PatternDatabase::setNumMoves(const RubiksCube& cube, const uint8_t numMoves)
  {
    return this->setNumMoves(this->getDatabaseIndex(cube), numMoves);
  }

  /**
   * Get the number of moves it takes to get to a scrambled cube state using
   * and index.  The index should be calculated using the getDatabaseIndex
   * method.  0xF (15) indicates that the state has not been set.
   * @param cube A cube instance.
   */
  uint8_t PatternDatabase::getNumMoves(const uint32_t ind) const
  {
    return this->database.get(ind);
  }

  /**
   * Get the number of moves it takes to get to a scrambled cube.  The index is
   * calculated using the getDatabaseIndex method.  0xF indicates that the
   * state has not been set.
   * @param cube A cube instance.
   */
  uint8_t PatternDatabase::getNumMoves(const RubiksCube& cube) const
  {
    return this->getNumMoves(this->getDatabaseIndex(cube));
  }

  /**
   * Get the number of moves it takes to get to a scrambled cube state.  A
   * depth and bound hint is passed to allow for an early out in aggregate
   * pattern databases.  For non-aggregate databases this is the same as
   * getNumMoves.
   */
  uint8_t PatternDatabase::getNumMovesEx(const uint32_t ind,
    const uint8_t boundHint, const uint8_t depthHint) const
  {
    return this->database.get(ind);
  }

  /**
   * Get the number of moves it takes to get to a scrambled cube state using a
   * cube instance.
   */
  uint8_t PatternDatabase::getNumMovesEx(const RubiksCube& cube,
    const uint8_t boundHint, const uint8_t depthHint) const
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

  /**
   * Write the database to a file.
   */
  void PatternDatabase::toFile(const string& filePath) const
  {
    ofstream writer(filePath, std::ios::out | std::ios::binary | std::ios::trunc);

    if (!writer.is_open())
      throw RubiksCubeException("Failed to open file for writing.");

    writer.write(
      reinterpret_cast<const char*>(this->database.data()),
      this->database.storageSize());

    writer.close();
  }

  /**
   * Read the database from a file.  Returns true if the database file exists
   * and is loaded, otherwise returns false.
   */
  bool PatternDatabase::fromFile(const string& filePath)
  {
    ifstream reader(filePath, std::ios::in | std::ios::ate);

    if (!reader.is_open())
      return false;

    size_t fileSize = reader.tellg();

    if (fileSize != this->database.storageSize())
    {
      reader.close();
      throw RubiksCubeException("Database file appears to be corrupt.  Wrong size.");
    }

    reader.seekg(0, std::ios::beg);
    reader.read(
      reinterpret_cast<char*>(this->database.data()),
      this->database.storageSize());
    reader.close();
    this->numItems = this->size;

    return true;
  }

  /**
   * Inflate the underlying array for faster access.
   */
  vector<uint8_t> PatternDatabase::inflate() const
  {
    vector<uint8_t> inflated;

    this->database.inflate(inflated);

    return inflated;
  }

  /**
   * Reset the pattern database, clearing all cube states.
   */
  void PatternDatabase::reset()
  {
    if (this->numItems != 0)
    {
      this->database.reset(0xFF);
      this->numItems = 0;
    }
  }
}

