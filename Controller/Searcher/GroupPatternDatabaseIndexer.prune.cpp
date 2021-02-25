#include "GroupPatternDatabaseIndexer.h"

namespace busybin
{
  /**
   * Search the cube until a DatabaseGoal is satisfied.  This is a custom IDDFS
   * search that indexes a database for use with and IDA* search.
   * @param goal The goal to achieve (isSatisfied is called on the goal).
   * @param groupGoal A gaol that satisfies a group, e.g. all edges oriented
   * for Thistlethwaite's G1 group.
   * @param cube A cube instance.
   * @param seenDB A PatternDatabase instance that's used to keep track of
   * states that have been seen.
   * @param moveStore A MoveStore instance for retrieving moves.
   * @param bound Search depth boundary.
   * @param curDepth Current search depth.
   * @param lastMove The last move (for pruning).
   * @param parentDist Parent's distance to a node that satisfies the group
   * goal.
   * @param solved Set to true when the last state is indexed.
   */
  unsigned GroupPatternDatabaseIndexer::findGoal(
    Goal& goal,
    Goal& groupGoal,
    RubiksCubeIndexModel& cube,
    PatternDatabase& seenDB,
    MoveStore& moveStore,
    const unsigned bound,
    unsigned curDepth,
    const MOVE lastMove,
    const unsigned parentDist,
    bool& solved
  ) const
  {
    bool groupSatisfied = groupGoal.isSatisfied(cube);
    uint32_t dbInd = seenDB.getDatabaseIndex(cube);

    // Distance from this state to the nearest state that satisfies the group.
    // It starts at the distance through the parent, but may be updated below
    // if the distance through a child is nearer.
    unsigned dist = groupSatisfied ? 0 : parentDist + 1;

    if (!groupSatisfied)
    {
      // This state may have been seen before, and the existing distance may
      // be shorter than the distance through the parent.
      unsigned dbDist = seenDB.getNumMoves(dbInd);

      if (dbDist < dist)
        dist = dbDist;
    }

    // Store the number of moves in the seen database for pruning (again, this
    // may be updated below).
    // TODO: Check if prunable.  Maybe?
    // TODO: This should probably be the depth.  The state can be pruned if the
    // node has been seen at an earlier depth (but not an equal depth, due to 
    // re-indexing).
    seenDB.setNumMoves(dbInd, dist);
    goal.index(cube, dist);

    // Check for solutions at the leaf nodes.
    if (curDepth == bound)
    {
      if (goal.isSatisfied(cube))
        solved = true;

      return dist;
    }

    MovePruner    pruner;
    const uint8_t numMoves = moveStore.getNumMoves();
    bool          childCloser = false;

    do
    {
      childCloser = false;

      for (uint8_t i = 0; i < numMoves && !childCloser; ++i)
      {
        MOVE move = moveStore.getMove(i);

        // Basic pruning of redundant and commutative moves.
        if (curDepth > 0 && pruner.prune(move, lastMove))
          continue;

        cube.move(move);

        unsigned nodeDepth = curDepth + 1;
        unsigned childDist = this->findGoal(goal, groupGoal, cube, seenDB,
          moveStore, bound, nodeDepth, move, dist, solved);
        unsigned distThroughChild = childDist + 1;

        cube.invert(move);

        // If the distance through the child is nearer than the distance
        // through the parent, then this node needs to get reindexed and all
        // children need to be rechecked.
        if (distThroughChild < dist)
        {
          childCloser = true;
          dist = distThroughChild;
          goal.index(cube, dist);
          seenDB.setNumMoves(cube, dist); // TODO: If depth is used, this won't be needed.
        }
      }
    }
    while (childCloser);

    return dist;
  }

  /**
   * Search the cube until goal is reached.  This is a custom IDDFS search that
   * indexes a database for a group.
   * @param goal The goal to achieve (isSatisfied is called on the goal).
   * @param groupGoal A gaol that satisfies a group, e.g. all edges oriented
   * for Thistlethwaite's G1 group.
   * @param cube A cube instance.
   * @param seenDB A PatternDatabase instance that's used to keep track of
   * states that have been seen.
   * @param moveStore A MoveStore instance for retrieving moves.
   */
  void GroupPatternDatabaseIndexer::findGoal(
    Goal& goal,
    Goal& groupGoal,
    RubiksCubeIndexModel& cube,
    PatternDatabase& seenDB,
    MoveStore& moveStore
  ) const
  {
    bool      solved = false;
    unsigned  bound = 0;
    AutoTimer timer;
    
    while (!solved)
    {
      this->findGoal(goal, groupGoal, cube, seenDB, moveStore, ++bound, 0,
        (MOVE)0xFF, 0, solved);

      // Reset the database of seen cube states.
      seenDB.reset();
      seenDB.setNumMoves(cube, 0);

      cout << "Group Indexer: Finished depth " << bound << ".  Elapsed time "
           << timer.getElapsedSeconds() << "s." << endl;
    }

    cout << "Group Indexer: Goal reached.  Elapsed time "
         << timer.getElapsedSeconds() << "s." << endl;
  }
}

