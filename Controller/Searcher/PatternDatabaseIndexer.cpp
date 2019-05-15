#include "PatternDatabaseIndexer.h"

namespace busybin
{
  /**
   * Search the cube until goal is reached and return the moves required
   * to acieve goal.  This is basically a non-recursive IDDFS search.
   * @param goal The goal to achieve (isSatisfied is called on the goal).
   * @param solvedCube A solved cube instance.
   * @param seenDB A PatternDatabase instance that's used to keep track of
   * states that have been seen.
   */
  void PatternDatabaseIndexer::findGoal(Goal& goal,
    RubiksCubeIndexModel& solvedCube, PatternDatabase& seenDB)
  {
    typedef RubiksCube::MOVE MOVE;

    AutoTimer   timer;
    MovePruner  pruner;
    unsigned    curDepth = 0;
    unsigned    indCount = 0;
    stack<Node> nodeStack;
    Node        curNode;

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
        nodeStack.push({solvedCube, 0xFF, 0});

        // Reset the database of seen cube states.
        seenDB.reset();
        seenDB.setNumMoves(solvedCube, 0);
      }

      curNode = nodeStack.top();
      nodeStack.pop();

      for (uint8_t i = 0; i < 18; ++i)
      {
        if (curNode.depth == 0 || !pruner.prune((MOVE)i, (MOVE)curNode.moveInd))
        {
          RubiksCubeIndexModel cubeCopy(curNode.cube);
          uint8_t              cubeCopyDepth = (uint8_t)(curNode.depth + 1);

          cubeCopy.move((MOVE)i);

          // This cube state may have been encountered at an earlier depth, at
          // which case it can be skipped.
          uint32_t dbInd = seenDB.getDatabaseIndex(cubeCopy);

          if (seenDB.getNumMoves(dbInd) >= cubeCopyDepth)
          {
            seenDB.setNumMoves(dbInd, cubeCopyDepth);

            // Index at the leaf level.
            if ((unsigned)(cubeCopyDepth) == curDepth)
            {
              if (goal.index(cubeCopy, cubeCopyDepth))
                ++indCount;
            }
            else
              nodeStack.push({cubeCopy, i, (uint8_t)(cubeCopyDepth)});
          }
        }
      }
    }
  }
}

