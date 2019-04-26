#include "KorfPatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage, storing pointers to the three aggregate
   * dbs.
   */
  KorfPatternDatabase::KorfPatternDatabase(
    const CornerPatternDatabase* pCornerDB,
    const EdgeG1PatternDatabase* pEdgeG1DB,
    const EdgeG2PatternDatabase* pEdgeG2DB) :
    PatternDatabase(0),
    pCornerDB(pCornerDB),
    pEdgeG1DB(pEdgeG1DB),
    pEdgeG2DB(pEdgeG2DB)
  {
  }

  /**
   * Get the estimated number of moves it would take to get from a cube state
   * to a scrambled state.  The estimate is the max of the corner and edge
   * databases' number of moves.
   */
  unsigned char KorfPatternDatabase::getNumMoves(const RubiksCubeModel& cube) const
  {
    uchar cornerMoves = this->pCornerDB->getNumMoves(cube);
    uchar edgeG1Moves = this->pEdgeG1DB->getNumMoves(cube);
    uchar edgeG2Moves = this->pEdgeG2DB->getNumMoves(cube);

    if (cornerMoves == 0xF || edgeG1Moves == 0xF || edgeG2Moves == 0xF)
      throw RubiksCubeException("Fatal: Scramble not indexed in one of the databases.");

    return max({cornerMoves, edgeG1Moves, edgeG2Moves});
  }

  uint32_t KorfPatternDatabase::getDatabaseIndex(const RubiksCubeModel& cube) const
  {
    throw RubiksCubeException("KorfPatternDatabase::getDatabaseIndex not implemented.");
  }

  bool KorfPatternDatabase::setNumMoves(const RubiksCubeModel& cube, const uchar numMoves)
  {
    throw RubiksCubeException("KorfPatternDatabase::setNumMoves not implemented.");
  }

  bool KorfPatternDatabase::setNumMoves(const uint32_t ind, const uchar numMoves)
  {
    throw RubiksCubeException("KorfPatternDatabase::setNumMoves not implemented.");
  }

  unsigned char KorfPatternDatabase::getNumMoves(const uint32_t ind) const
  {
    throw RubiksCubeException("KorfPatternDatabase::getNumMoves not implemented.");
  }

  size_t KorfPatternDatabase::getSize() const
  {
    throw RubiksCubeException("KorfPatternDatabase::getSize not implemented.");
  }

  size_t KorfPatternDatabase::getNumItems() const
  {
    throw RubiksCubeException("KorfPatternDatabase::getNumItems not implemented.");
  }

  bool KorfPatternDatabase::isFull() const
  {
    throw RubiksCubeException("KorfPatternDatabase::isFull not implemented.");
  }

  void KorfPatternDatabase::toFile(const string& filePath) const
  {
    throw RubiksCubeException("KorfPatternDatabase::toFile not implemented.");
  }

  bool KorfPatternDatabase::fromFile(const string& filePath)
  {
    throw RubiksCubeException("KorfPatternDatabase::fromFile not implemented.");
  }
}

