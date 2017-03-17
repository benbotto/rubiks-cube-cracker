#include "CubeSearcher.h"

namespace busybin
{
  /**
   * Search the cube until goal is reached and return the moves required
   * to acieve goal.
   * @param goal The goal to achieve (isSatisfied is called on the goal).
   * @param cube The cube to search.
   * @param moveStore A MoveStore instance for retrieving moves.
   */
  vector<string> CubeSearcher::findGoal(Goal& goal, RubiksCubeModel& cube, MoveStore& moveStore)
  {
    AutoTimer      timer;
    unsigned       maxDepth = 0;
    vector<string> moves;

    while (!this->findGoal(goal, cube, moveStore, 0, maxDepth, moves))
    {
      cout << "Finished depth " << maxDepth << ".  Elapsed time " 
           << timer.getElapsedSeconds() << "s." << endl;

      ++maxDepth;
    }
    
    return moves;
  }

  /**
   * Find goal.
   * @param goal The goal to achieve.
   * @param cube The cube to search.
   * @param moveStore A MoveStore instance for retrieving moves.
   * @param depth The current depth of the search.
   * @param maxDepth The maximum depth.
   * @param moves A vector of moves that will be filled.
   */
  bool CubeSearcher::findGoal(Goal& goal, RubiksCubeModel& cube, MoveStore& moveStore,
    unsigned depth, unsigned maxDepth, vector<string>& moves)
  {
    bool     solved   = false;
    unsigned numMoves = moveStore.getNumMoves();

    // Check if the goal is satisfied.
    if (depth == maxDepth)
      return goal.isSatisfied(cube);

    for (unsigned i = 0; i < numMoves && !solved; ++i)
    {
      string move = moveStore.getMove(i);

      if (!this->prune(move, moveStore, moves))
      {
        // Apply the next move.
        moves.push_back(move);
        moveStore.getMoveFunc(move)();

        // If this move satisfies the goal break out of the loop.
        if (this->findGoal(goal, cube, moveStore, depth + 1, maxDepth, moves))
          solved = true;
        else
          moves.pop_back();

        // Revert the move.
        moveStore.getInverseMoveFunc(move)();
      }
    }

    return solved;
  }

  /**
   * Check if the next move should be skipped.
   * @param move The next move, not yet applied.
   * @param moveStore A MoveStore instance for retrieving moves.
   * @param moves A vector of moves that will be filled.
   */
  bool CubeSearcher::prune(const string& move, const MoveStore& moveStore, const vector<string>& moves) const
  {
    if (moves.size() == 0)
      return false;

    string lastMove = moves.back();

    // If the last move is the same as this move, no reason to attempt it.
    // e.g. L L is the same as L2.  L2 L2 is a 360 degree twist.
    // Two moves that can be accomplished in one.  For instance, L2 L is the
    // same as L'.  L2 L' is the same as L.  Commutative.
    // In other words, if two moves  on the same side occur successively,
    // prune.
    if (move.at(0) == lastMove.at(0)) return true;

    // Redundant moves.  For example, F B is the same as B F.
    if (move == "F"  && lastMove == "B")  return true;
    if (move == "F2" && lastMove == "B2") return true;
    if (move == "L"  && lastMove == "R")  return true;
    if (move == "L2" && lastMove == "R2") return true;
    if (move == "U"  && lastMove == "D")  return true;
    if (move == "U2" && lastMove == "D2") return true;
    
    return false;
  }
}

