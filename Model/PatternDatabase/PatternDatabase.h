#ifndef _BUSYBIN_PATTERN_DATABASE_
#define _BUSYBIN_PATTERN_DATABASE_

#include "../RubiksCube.h"
#include "../../Util/NibbleArray.h"
#include "../../Util/RubiksCubeException.h"
#include <cstdint>
#include <cstddef>
using std::size_t;
#include <fstream>
using std::ofstream;
using std::ifstream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <array>
using std::array;

namespace busybin
{
  /**
   * Base class for the corner and edge pattern databases.  Provides
   * index-based lookups for the number of moves required to get a scrambled
   * cube to the solved state.
   */
  class PatternDatabase
  {
    NibbleArray database;

    PatternDatabase();

    size_t size;
    size_t numItems;

  public:
    PatternDatabase(const size_t size);
    virtual uint32_t getDatabaseIndex(const RubiksCube& cube) const = 0;
    virtual bool setNumMoves(const RubiksCube& cube, const uint8_t numMoves);
    virtual bool setNumMoves(const uint32_t ind, const uint8_t numMoves);
    virtual uint8_t getNumMoves(const RubiksCube& cube) const;
    virtual uint8_t getNumMoves(const uint32_t ind) const;
    virtual uint8_t getNumMovesEx(const RubiksCube& cube,
      const uint8_t boundHint, const uint8_t depthHint) const;
    virtual uint8_t getNumMovesEx(const uint32_t ind,
      const uint8_t boundHint, const uint8_t depthHint) const;
    virtual size_t getSize() const;
    virtual size_t getNumItems() const;
    virtual bool isFull() const;
    virtual void toFile(const string& filePath) const;
    virtual bool fromFile(const string& filePath);
    virtual vector<uint8_t> inflate() const;
    virtual void reset();
  };
}

#endif

