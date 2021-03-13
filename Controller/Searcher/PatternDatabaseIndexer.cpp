#include "PatternDatabaseIndexer.h"

namespace busybin
{
  /**
   * Search the cube until goal is reached and return the moves required
   * to acieve goal.  This is basically a non-recursive IDDFS search.
   * @param goal The goal to achieve (isSatisfied is called on the goal).
   * @param solvedCube A solved cube instance.
   * @param moveStore A MoveStore instance for retrieving moves.
   */
  void PatternDatabaseIndexer::findGoal(
    DatabaseGoal& goal,
    RubiksCubeIndexModel& solvedCube,
    MoveStore& moveStore
  )
  {
    typedef RubiksCube::MOVE MOVE;

    AutoTimer   timer;
    MovePruner  pruner;
    unsigned    curDepth = 0;
    unsigned    indCount = 0;
    stack<Node> nodeStack;
    Node        curNode;
    uint8_t     numMoves = moveStore.getNumMoves();

    // Index the root node in the database.
    goal.index(solvedCube, 0);
    ++indCount;

    while (!goal.isSatisfied(solvedCube))
    {
      // When the stack is empty, a depth is complete.
      if (nodeStack.empty())
      {
        cout << "Indexer: Finished depth " << curDepth << ".  Elapsed time "
             << timer.getElapsedSeconds() << "s.  Indexed " << indCount
             << " states." << endl;

        ++curDepth;

        // Push on the root node.
        nodeStack.push({solvedCube, (MOVE)0xFF, 0});
      }

      curNode = nodeStack.top();
      nodeStack.pop();

      for (uint8_t i = 0; i < numMoves; ++i)
      {
        MOVE move = moveStore.getMove(i);

        if (curNode.depth == 0 || !pruner.prune(move, curNode.move))
        {
          RubiksCubeIndexModel cubeCopy(curNode.cube);
          uint8_t              cubeCopyDepth = (uint8_t)(curNode.depth + 1);

          cubeCopy.move(move);

          // This cube state may have been encountered at an earlier depth, in
          // which case it can be skipped.
          uint32_t dbInd = goal.getDatabaseIndex(cubeCopy);

          if (goal.getNumMoves(dbInd) < cubeCopyDepth)
            continue;

          // Index at the leaf level.
          if ((unsigned)(cubeCopyDepth) == curDepth)
          {
            if (goal.index(dbInd, cubeCopyDepth))
              ++indCount;
          }
          else
            nodeStack.push({cubeCopy, move, (uint8_t)cubeCopyDepth});
        }
      }
    }
  }
}
