#include "GroupPatternDatabaseIndexer.h"

namespace busybin
{
  /**
   * Search the cube until goal is reached and return the moves required to
   * acieve goal.  This is a custom IDDFS search that indexes a database for a
   * group.
   * @param goal The goal to achieve (isSatisfied is called on the goal).
   * @param groupGoal A gaol that satisfies a group, e.g. all edges oriented
   * for Thistlethwaite's G1 group.
   * @param solvedCube A solved cube instance.
   * @param seenDB A PatternDatabase instance that's used to keep track of
   * states that have been seen.
   * @param moveStore A MoveStore instance for retrieving moves.
   */
  void GroupPatternDatabaseIndexer::findGoal(
    Goal& goal,
    Goal& groupGoal,
    RubiksCubeIndexModel& solvedCube,
    PatternDatabase& seenDB,
    MoveStore& moveStore
  ) const
  {
    typedef RubiksCube::MOVE MOVE;

    AutoTimer     timer;
    MovePruner    pruner;
    unsigned      curDepth = 0;
    unsigned      indCount = 0;
    stack<Node>   nodeStack;
    Node          curNode;
    const uint8_t numMoves = moveStore.getNumMoves();

    // Index the root node in the database.
    goal.index(solvedCube, 0);
    ++indCount;

    while (!goal.isSatisfied(solvedCube))
    {
      // When the stack is empty, a depth is complete.
      if (nodeStack.empty())
      {
        cout << "Group Indexer: Finished depth " << curDepth << ".  Elapsed time "
             << timer.getElapsedSeconds() << "s.  Indexed " << indCount
             << " states." << endl;

        ++curDepth;

        // Push on the root node.
        nodeStack.push({solvedCube, (MOVE)0xFF, 0, 0});

        // Reset the database of seen cube states.
        seenDB.reset();
        seenDB.setNumMoves(solvedCube, 0);
      }

      curNode = nodeStack.top();
      nodeStack.pop();

      for (uint8_t i = 0; i < numMoves; ++i)
      {
        MOVE move = moveStore.getMove(i);

        if (curNode.depth == 0 || !pruner.prune(move, curNode.move))
        {
          // Copy the cube and move it.
          RubiksCubeIndexModel cubeCopy(curNode.cube);

          cubeCopy.move(move);

          // Depth of this node (e.g. twists to get here).
          uint8_t depth = (uint8_t)(curNode.depth + 1);

          // Non-leaf node that satisfies the group.  It's pushed with a
          // distance of 0.
          if (groupGoal.isSatisfied(cubeCopy) && curDepth < depth)
          {
            nodeStack.push({cubeCopy, move, depth, 0});
          }
          else
          {
            // Distance from the nearest node that satisfies the group goal.
            uint8_t distanceToGroup = (uint8_t)(curNode.distanceToGroup + 1);

            // This cube state may have been encountered before, and with a shorter
            // distance to a group goal.  If so, this node can be skipped.
            uint32_t dbInd = seenDB.getDatabaseIndex(cubeCopy);

            if (seenDB.getNumMoves(dbInd) >= distanceToGroup)
            {
              seenDB.setNumMoves(dbInd, distanceToGroup);

              // Index at the leaf level.
              if ((unsigned)depth == curDepth)
              {
                if (goal.index(cubeCopy, distanceToGroup))
                  ++indCount;
              }
              else
                nodeStack.push({cubeCopy, move, depth, distanceToGroup});
            }
          }
        }
      }
    }

    cout << "Group Indexer: Goal reached.  Elapsed time "
         << timer.getElapsedSeconds() << "s.  Indexed " << indCount
         << " states." << endl;
  }
}

