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
    EdgeG2PatternDatabase* pEdgeG2DB,
    EdgePermutationPatternDatabase* pEdgePermDB) :
    PatternDatabase(0),
    inflated(false),
    pCornerDB(pCornerDB),
    pEdgeG1DB(pEdgeG1DB),
    pEdgeG2DB(pEdgeG2DB),
    pEdgePermDB(pEdgePermDB)
  {
  }

  /**
   * Get the estimated number of moves it would take to get from a cube state
   * to a scrambled state.  The estimate is the max of all the databases.
   */
  uint8_t KorfPatternDatabase::getNumMoves(const RubiksCube& cube) const
  {
    uint8_t cornerMoves;
    uint8_t edgeG1Moves;
    uint8_t edgeG2Moves;
    uint8_t edgePermMoves;

    if (this->inflated)
    {
      cornerMoves   = this->cornerDBInflated[this->pCornerDB->getDatabaseIndex(cube)];
      edgeG1Moves   = this->edgeG1DBInflated[this->pEdgeG1DB->getDatabaseIndex(cube)];
      edgeG2Moves   = this->edgeG2DBInflated[this->pEdgeG2DB->getDatabaseIndex(cube)];
      edgePermMoves = this->edgePermDBInflated[this->pEdgePermDB->getDatabaseIndex(cube)];
    }
    else
    {
      cornerMoves   = this->pCornerDB->getNumMoves(cube);
      edgeG1Moves   = this->pEdgeG1DB->getNumMoves(cube);
      edgeG2Moves   = this->pEdgeG2DB->getNumMoves(cube);
      edgePermMoves = this->pEdgePermDB->getNumMoves(cube);
    }

    // This is for debugging, since a state should never return 15 moves.
    // However, this database can be used for more than just the distance to
    // the solved state, such as duplicate state detection, so this check can't
    // be enabled in release mode.
    //if (cornerMoves == 0xF || edgeG1Moves == 0xF || edgeG2Moves == 0xF || edgePermMoves == 0xF)
    //  throw RubiksCubeException("Fatal: Scramble not indexed in one of the databases.");

    return max({cornerMoves, edgeG1Moves, edgeG2Moves, edgePermMoves});
  }

  /**
   * Get the estimated number of moves it would take to get from a cube state
   * to a scrambled state.  This is faster than getNumMoves because as soon as
   * one of the databases' estimates exceeds the boundHint this method returns.
   * Use this method with an inflated database or else it's the same as
   * getNumMoves.
   */
  uint8_t KorfPatternDatabase::getNumMovesEx(const RubiksCube& cube,
    const uint8_t boundHint, const uint8_t depthHint) const
  {
    uint8_t max, estMoves;

    if (this->inflated)
    {
      // Check the estimated moves from each database, and return it as soon
      // as one exceeds the bound.
      max = estMoves = this->cornerDBInflated[this->pCornerDB->getDatabaseIndex(cube)];

      if (estMoves + depthHint > boundHint)
        return estMoves;

      estMoves = this->edgeG1DBInflated[this->pEdgeG1DB->getDatabaseIndex(cube)];

      if (estMoves + depthHint > boundHint)
        return estMoves;

      if (estMoves > max)
        max = estMoves;

      estMoves = this->edgeG2DBInflated[this->pEdgeG2DB->getDatabaseIndex(cube)];

      if (estMoves + depthHint > boundHint)
        return estMoves;

      if (estMoves > max)
        max = estMoves;

      estMoves = this->edgePermDBInflated[this->pEdgePermDB->getDatabaseIndex(cube)];

      if (estMoves + depthHint > boundHint)
        return estMoves;

      if (estMoves > max)
        max = estMoves;

      // Return the max estimate if none exceeds the bound.
      return max;
    }
    else
    {
      return this->getNumMoves(cube);
    }
  }

  /**
   * Set the number of moves in all databases.  Returns true if any is changed.
   */
  bool KorfPatternDatabase::setNumMoves(const RubiksCube& cube, const uint8_t numMoves)
  {
    bool corner   = this->pCornerDB->setNumMoves(cube,   numMoves);
    bool edgeG1   = this->pEdgeG1DB->setNumMoves(cube,   numMoves);
    bool edgeG2   = this->pEdgeG2DB->setNumMoves(cube,   numMoves);
    bool edgePerm = this->pEdgePermDB->setNumMoves(cube, numMoves);

    return corner || edgeG1 || edgeG2 || edgePerm;
  }

  /**
   * Returns true if all databases are full.
   */
  bool KorfPatternDatabase::isFull() const
  {
    return this->pCornerDB->isFull() &&
           this->pEdgeG1DB->isFull() &&
           this->pEdgeG2DB->isFull() &&
           this->pEdgePermDB->isFull();
  }

  /**
   * Inflate all databases for faster access.
   */
  void KorfPatternDatabase::inflate()
  {
    this->cornerDBInflated   = this->pCornerDB->inflate();
    this->edgeG1DBInflated   = this->pEdgeG1DB->inflate();
    this->edgeG2DBInflated   = this->pEdgeG2DB->inflate();
    this->edgePermDBInflated = this->pEdgePermDB->inflate();

    this->inflated = true;
  }

  /**
   * Reset all three databases.
   */
  void KorfPatternDatabase::reset()
  {
    this->inflated = false;

    this->pCornerDB->reset();
    this->pEdgeG1DB->reset();
    this->pEdgeG2DB->reset();
    this->pEdgePermDB->reset();
  }

  uint32_t KorfPatternDatabase::getDatabaseIndex(const RubiksCube& cube) const
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

