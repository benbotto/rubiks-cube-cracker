#include "PatternDatabaseIndexer.h"

namespace busybin
{
  /**
   * Search the cube until goal is reached and return the moves required
   * to acieve goal.  This is basically a non-recursive IDDFS search.
   * @param goal The goal to achieve (isSatisfied is called on the goal).
   * @param solvedCube A solved cube instance.
   */
  void PatternDatabaseIndexer::findGoal(Goal& goal, RubiksCubeModel& solvedCube)
  {
    typedef RubiksCubeModel::MOVE MOVE;

    AutoTimer   timer;
    MovePruner  pruner;
    unsigned    curDepth = 0;
    unsigned    indCount = 1;
    stack<Node> nodeStack;
    Node        curNode;

    // Index the root node in the database.
    goal.index(solvedCube, 0);

    while (!goal.isSatisfied(solvedCube))
    {
      // When the stack is empty, a depth is complete.
      if (nodeStack.empty())
      {
        cout << "Indexer: Finished depth " << curDepth << ".  Elapsed time "
             << timer.getElapsedSeconds() << "s.  Indexed " << indCount
             << " states." << endl;

        // Push on the root node.
        nodeStack.push({solvedCube, 0xFF, 0});

        ++curDepth;
      }

      curNode = nodeStack.top();
      nodeStack.pop();

      for (uint8_t i = 0; i < 18; ++i)
      {
        if (curNode.depth == 0 || !pruner.prune((MOVE)i, (MOVE)curNode.moveInd))
        {
          RubiksCubeModel cubeCopy(curNode.cube);
          uint8_t         cubeCopyDepth = (uint8_t)(curNode.depth + 1);

          cubeCopy.move((MOVE)i);

          // Index at the leaf level.
          if ((unsigned)(cubeCopyDepth) == curDepth)
          {
            // Index the new state.
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

