#ifndef _BUSYBIN_KORF_PATTERN_DATABASE_
#define _BUSYBIN_KORF_PATTERN_DATABASE_

#include "CornerPatternDatabase.h"
#include "EdgeG1PatternDatabase.h"
#include "EdgeG2PatternDatabase.h"
#include "../../RubiksCubeModel.h"
#include "../PatternDatabase.h"
#include "../../../Util/RubiksCubeException.h"
#include <algorithm>
using std::max;
#include <cstdint>

namespace busybin
{
  /**
   * This is an aggregate class that combines the corner and two edge databases
   * needed for Korf's algorithm.  It's used as a heuristic in the IDA*
   * searcher.  Getting an item from this database returns the max number of
   * moves from the three databases.
   */
  class KorfPatternDatabase : public PatternDatabase
  {
    typedef unsigned char uchar;

    CornerPatternDatabase* pCornerDB;
    EdgeG1PatternDatabase* pEdgeG1DB;
    EdgeG2PatternDatabase* pEdgeG2DB;

  public:
    KorfPatternDatabase(
      CornerPatternDatabase* pCornerDB,
      EdgeG1PatternDatabase* pEdgeG1DB,
      EdgeG2PatternDatabase* pEdgeG2DB);

    uchar getNumMoves(const RubiksCubeModel& cube) const;
    bool setNumMoves(const RubiksCubeModel& cube, const uchar numMoves);
    bool isFull() const;

    // All unimplemented.
    uint32_t getDatabaseIndex(const RubiksCubeModel& cube) const;
    bool setNumMoves(const uint32_t ind, const uchar numMoves);
    uchar getNumMoves(const uint32_t ind) const;
    size_t getSize() const;
    size_t getNumItems() const;
    void toFile(const string& filePath) const;
    bool fromFile(const string& filePath);
  };
}

#endif