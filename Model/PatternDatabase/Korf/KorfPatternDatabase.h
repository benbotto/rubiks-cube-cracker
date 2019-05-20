#ifndef _BUSYBIN_KORF_PATTERN_DATABASE_
#define _BUSYBIN_KORF_PATTERN_DATABASE_

#include "CornerPatternDatabase.h"
#include "EdgeG1PatternDatabase.h"
#include "EdgeG2PatternDatabase.h"
#include "EdgePermutationPatternDatabase.h"
#include "../../RubiksCube.h"
#include "../PatternDatabase.h"
#include "../../../Util/RubiksCubeException.h"
#include <algorithm>
using std::max;
#include <cstdint>
#include <vector>
using std::vector;

namespace busybin
{
  /**
   * This is an aggregate class that combines all the pattern databases needed
   * for Korf's algorithm (plus more).  It's used as a heuristic in the IDA*
   * searcher.  Getting an item from this database returns the max number of
   * moves from the databases.
   */
  class KorfPatternDatabase : public PatternDatabase
  {
    bool inflated;

    CornerPatternDatabase*          pCornerDB;
    EdgeG1PatternDatabase*          pEdgeG1DB;
    EdgeG2PatternDatabase*          pEdgeG2DB;
    EdgePermutationPatternDatabase* pEdgePermDB;

    vector<uint8_t> cornerDBInflated;
    vector<uint8_t> edgeG1DBInflated;
    vector<uint8_t> edgeG2DBInflated;
    vector<uint8_t> edgePermDBInflated;

  public:
    KorfPatternDatabase(
      CornerPatternDatabase* pCornerDB,
      EdgeG1PatternDatabase* pEdgeG1DB,
      EdgeG2PatternDatabase* pEdgeG2DB,
      EdgePermutationPatternDatabase* pEdgePermDB);

    uint8_t getNumMoves(const RubiksCube& cube) const;
    uint8_t getNumMovesEx(const RubiksCube& cube,
      const uint8_t boundHint, const uint8_t depthHint) const;
    bool setNumMoves(const RubiksCube& cube, const uint8_t numMoves);
    bool isFull() const;
    void inflate();
    void reset();

    // All unimplemented.
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
    bool setNumMoves(const uint32_t ind, const uint8_t numMoves);
    uint8_t getNumMoves(const uint32_t ind) const;
    size_t getSize() const;
    size_t getNumItems() const;
    void toFile(const string& filePath) const;
    bool fromFile(const string& filePath);
    vector<uint8_t> inflate() const;
  };
}

#endif
