#include "CubeSearcher.h"

namespace busybin
{
  /**
   * Initialize.
   * @param cube The cube (must stay in scope).
   * @param moveStore A reference to the move storage.
   */
  CubeSearcher::CubeSearcher(RubiksCubeModel& cube, MoveStore& moveStore) :
    pCube(&cube), pMoveStore(&moveStore)
  {
  }

  /**
   * Search the cube until goal is reached and return the moves required
   * to acieve goal.
   * @param goal The goal to achieve (isSatisfied is called on the goal).
   */
  vector<string> CubeSearcher::findGoal(Goal& goal)
  {
    unsigned maxDepth = 0;
    vector<string> moves;
    AutoTimer timer;

    while (!this->findGoal(goal, 0, maxDepth, moves))
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
   * @param depth The current depth of the search.
   * @param maxDepth The maximum depth.
   * @param moves A vector of moves that will be filled.
   */
  bool CubeSearcher::findGoal(Goal& goal, unsigned depth,
    unsigned maxDepth, vector<string>& moves)
  {
    bool solved = false;

    // Check if the goal is satisfied.
    if (goal.isSatisfied(*this->pCube))
      return true;

    if (depth == maxDepth)
      return false;

    for (unsigned i = 0; i < this->pMoveStore->getNumMoves() && !solved; ++i)
    {
      // Apply the next move.
      string move = this->pMoveStore->getMove(i);
      moves.push_back(move);
      this->pMoveStore->getMoveFunc(move)();

      // If this move satisfies the goal break out of the loop.
      if (this->findGoal(goal, depth + 1, maxDepth, moves))
        solved = true;
      else
        moves.pop_back();

      // Revert the move.
      this->pMoveStore->getInverseMoveFunc(move)();
    }

    return solved;
  }
}

