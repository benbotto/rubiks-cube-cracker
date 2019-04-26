#include "IDACubeSearcher.h"

namespace busybin
{
  /**
   * Initialize the searcher with a PatternDatabase instance.
   * @param pPatternDatabase A pointer to a PatternDatabase that will be used
   * to get an estimated distance from a scramble to the solved state.
   */
  IDACubeSearcher::IDACubeSearcher(const PatternDatabase* pPatternDB) :
    CubeSearcher(), pPatternDB(pPatternDB)
  {
  }

  /**
   * Search the cube until goal is reached and return the moves required
   * to achieve goal.
   * @param goal The goal to achieve (isSatisfied is called on the goal).
   * @param cube The cube to search.
   * @param moveStore A MoveStore instance for retrieving moves.
   */
  vector<string> IDACubeSearcher::findGoal(Goal& goal, RubiksCubeModel& cube,
    MoveStore& moveStore)
  {
    AutoTimer      timer;
    vector<string> moves;
    uint8_t        bound  = this->pPatternDB->getNumMoves(cube);
    bool           solved = false;

    while (!solved)
    {
      uint8_t newBound = this->findGoal(goal, cube, moveStore, bound, moves, solved);

      cout << "IDA*: Finished bound " << (unsigned)bound << ".  Elapsed time "
           << timer.getElapsedSeconds() << "s." << endl;

      bound = newBound;
    }

    return moves;
  }

  /**
   * Private helper method that recursively searches for a goal, and cuts off
   * when bound is reached.
   * @param goal The goal to achieve.
   * @param cube The cube to search.
   * @param moveStore A MoveStore instance for retrieving moves.
   * @param bound The cut-off point, which is an maximum estimated distance from
   * the root state to the solved state.
   * @param moves A vector of moves that will be filled.
   * @param solved A boolean that will be set to true when solved.
   */
  uint8_t IDACubeSearcher::findGoal(Goal& goal, RubiksCubeModel& cube, MoveStore& moveStore,
    uint8_t bound, vector<string>& moves, bool& solved)
  {
    typedef priority_queue<PrioritizedMove, vector<PrioritizedMove>,
      greater<PrioritizedMove> > moveQueue_t;

    uint8_t numMoves = moveStore.getNumMoves();

    // Estimated number of moves to the solved state from here.
    uint8_t estMovesFromHere = this->pPatternDB->getNumMoves(cube);

    // Estimated number of moves from the root to the solved state through this scramble.
    uint8_t estMovesFromRoot = moves.size() + estMovesFromHere;

    // This holds the next bound, which is the minimum cost that's greater than
    // the current bound.
    uint8_t min = 0xFF;

    // This is used to order the moves by priority.
    moveQueue_t successors;

    if (estMovesFromRoot > bound)
      return estMovesFromRoot;

    // This assumes that the heuristic returns 0 cost when the cube is solved.
    if (estMovesFromHere == 0 && goal.isSatisfied(cube)) {
      solved = true;
      return estMovesFromRoot;
    }

    // Set up the successor nodes in order.
    for (uint8_t i = 0; i < numMoves && !solved; ++i)
    {
      string move = moveStore.getMove(i);

      if (!this->prune(move, moves))
      {
        // Apply the next move.
        moveStore.getMoveFunc(move)();

        // Get the estimated moves to solved.
        uint8_t estSuccMoves = moves.size() + 1 + this->pPatternDB->getNumMoves(cube);

        // Revert the move.
        moveStore.getInverseMoveFunc(move)();

        // Queue the successor.
        successors.push({i, estSuccMoves});
      }
    }

    while (!successors.empty() && !solved)
    {
      uint8_t moveInd = successors.top().moveInd;
      string  move    = moveStore.getMove(moveInd);

      successors.pop();

      // Apply the next move.
      moves.push_back(move);
      moveStore.getMoveFunc(move)();

      uint8_t succCost = this->findGoal(goal, cube, moveStore, bound, moves, solved);

      if (!solved)
      {
        moves.pop_back();

        if (succCost < min)
          min = succCost;
      }

      // Revert the move.
      moveStore.getInverseMoveFunc(move)();
    }

    return min;
  }
}

