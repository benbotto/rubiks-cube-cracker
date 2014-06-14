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
      // Apply the next move.
      string move = moveStore.getMove(i);
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

    return solved;
  }
}

