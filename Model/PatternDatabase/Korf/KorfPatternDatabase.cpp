#include "KorfPatternDatabase.h"

namespace busybin
{
  /**
   * Initialize the database storage, storing pointers to the three aggregate
   * dbs.
   */
  KorfPatternDatabase::KorfPatternDatabase(
    CornerPatternDatabase* pCornerDB,
    EdgeG1PatternDatabase* pEdgeG1DB,
    EdgeG2PatternDatabase* pEdgeG2DB) :
    PatternDatabase(0),
    inflated(false),
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
  uint8_t KorfPatternDatabase::getNumMoves(const RubiksCubeModel& cube) const
  {
    uint8_t cornerMoves;
    uint8_t edgeG1Moves;
    uint8_t edgeG2Moves;

    if (this->inflated)
    {
      cornerMoves = this->cornerDBInflated[this->pCornerDB->getDatabaseIndex(cube)];
      edgeG1Moves = this->edgeG1DBInflated[this->pEdgeG1DB->getDatabaseIndex(cube)];
      edgeG2Moves = this->edgeG2DBInflated[this->pEdgeG2DB->getDatabaseIndex(cube)];
    }
    else
    {
      cornerMoves = this->pCornerDB->getNumMoves(cube);
      edgeG1Moves = this->pEdgeG1DB->getNumMoves(cube);
      edgeG2Moves = this->pEdgeG2DB->getNumMoves(cube);
    }

    if (cornerMoves == 0xF || edgeG1Moves == 0xF || edgeG2Moves == 0xF)
      throw RubiksCubeException("Fatal: Scramble not indexed in one of the databases.");

    return max({cornerMoves, edgeG1Moves, edgeG2Moves});
  }

  /**
   * Set the number of moves in all three databases.  Returns true if any is
   * changed.
   */
  bool KorfPatternDatabase::setNumMoves(const RubiksCubeModel& cube, const uint8_t numMoves)
  {
    bool corner = this->pCornerDB->setNumMoves(cube, numMoves);
    bool edgeG1 = this->pEdgeG1DB->setNumMoves(cube, numMoves);
    bool edgeG2 = this->pEdgeG2DB->setNumMoves(cube, numMoves);

    return corner || edgeG1 || edgeG2;
  }

  /**
   * Returns true if all three databases are full.
   */
  bool KorfPatternDatabase::isFull() const
  {
    return this->pCornerDB->isFull() &&
           this->pEdgeG1DB->isFull() &&
           this->pEdgeG2DB->isFull();
  }

  /**
   * Inflate all three databases for faster access.
   */
  void KorfPatternDatabase::inflate()
  {
    this->cornerDBInflated = this->pCornerDB->inflate();
    this->edgeG1DBInflated = this->pEdgeG1DB->inflate();
    this->edgeG2DBInflated = this->pEdgeG2DB->inflate();

    this->inflated = true;
  }

  uint32_t KorfPatternDatabase::getDatabaseIndex(const RubiksCubeModel& cube) const
  {
    throw RubiksCubeException("KorfPatternDatabase::getDatabaseIndex not implemented.");
  }

  bool KorfPatternDatabase::setNumMoves(const uint32_t ind, const uint8_t numMoves)
  {
    throw RubiksCubeException("KorfPatternDatabase::setNumMoves not implemented.");
  }

  uint8_t KorfPatternDatabase::getNumMoves(const uint32_t ind) const
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

  void KorfPatternDatabase::toFile(const string& filePath) const
  {
    throw RubiksCubeException("KorfPatternDatabase::toFile not implemented.");
  }

  bool KorfPatternDatabase::fromFile(const string& filePath)
  {
    throw RubiksCubeException("KorfPatternDatabase::fromFile not implemented.");
  }

  vector<uint8_t> KorfPatternDatabase::inflate() const
  {
    throw RubiksCubeException("KorfPatternDatabase::inflate not implemented.");
  }
}

