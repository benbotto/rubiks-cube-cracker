#include "IDDFSCubeSearcher.h"

namespace busybin
{
  /**
   * Search the cube until goal is reached and return the moves required
   * to acieve goal.
   * @param goal The goal to achieve (isSatisfied is called on the goal).
   * @param cube The cube to search.
   * @param moveStore A MoveStore instance for retrieving moves.
   */
  vector<RubiksCube::MOVE> IDDFSCubeSearcher::findGoal(Goal& goal, RubiksCube& cube,
    MoveStore& moveStore)
  {
    AutoTimer       timer;
    unsigned        maxDepth = 0;
    vector<uint8_t> moveInds;

    while (!this->findGoal(goal, cube, moveStore, 0, maxDepth, moveInds))
    {
      cout << "IDDFS: Finished depth " << maxDepth << ".  Elapsed time "
           << timer.getElapsedSeconds() << "s." << endl;

      ++maxDepth;
    }

    return this->convertMoves(moveInds, moveStore);
  }

  /**
   * Private helper method that recursively searches for a goal, and cust off
   * when maxDepth is reached.
   * @param goal The goal to achieve.
   * @param cube The cube to search.
   * @param moveStore A MoveStore instance for retrieving moves.
   * @param depth The current depth of the search.
   * @param maxDepth The maximum depth.
   * @param moves A vector of moves that will be filled.
   */
  bool IDDFSCubeSearcher::findGoal(Goal& goal, RubiksCube& cube, MoveStore& moveStore,
    unsigned depth, unsigned maxDepth, vector<uint8_t>& moveInds)
  {
    bool    solved   = false;
    uint8_t numMoves = moveStore.getNumMoves();

    // Check if the goal is satisfied.
    if (depth == maxDepth)
    {
      // Index the cube state (some goals store a database).
      goal.index(cube, depth);

      return goal.isSatisfied(cube);
    }

    for (uint8_t i = 0; i < numMoves && !solved; ++i)
    {
      if (moveInds.size() == 0 ||
        !this->pruner.prune(moveStore.getMove(i), moveStore.getMove(moveInds.back())))
      {
        // Apply the next move.
        moveInds.push_back(i);
        moveStore.move(i);

        // If this move satisfies the goal break out of the loop.
        if (this->findGoal(goal, cube, moveStore, depth + 1, maxDepth, moveInds))
          solved = true;
        else
          moveInds.pop_back();

        // Revert the move.
        moveStore.invert(i);
      }
    }

    return solved;
  }
}

