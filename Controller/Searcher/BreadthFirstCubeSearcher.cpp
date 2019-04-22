#include "BreadthFirstCubeSearcher.h"

namespace busybin
{
  /**
   * Search the cube until goal is reached and return the moves required
   * to acieve goal.
   * @param goal The goal to achieve (isSatisfied is called on the goal).
   * @param cube The cube to search.
   * @param moveStore A MoveStore instance for retrieving moves.
   */
  vector<string> BreadthFirstCubeSearcher::findGoal(Goal& goal,
    RubiksCubeModel& cube, MoveStore& moveStore)
  {
    int16_t        numMoves = moveStore.getNumMoves();
    uint8_t        depth    = 0;
    unsigned       visited  = 0;
    queue<node>    moveQueue;
    AutoTimer      timer;
    vector<string> moves;

    // The corner database may be pre-populated from a file.
    if (goal.isSatisfied(cube))
      return moves;

    // The search starts at the root node.  It takes no moves to get there.
    moveQueue.push({0xFFFF, NULL, depth});
    goal.index(cube, depth);

    while (!moveQueue.empty())
    {
      // Next node in the queue.
      node curNode = moveQueue.front();
      moveQueue.pop();

      if (depth < curNode.depth)
      {
        cout << "BFS: Finished depth " << (unsigned)depth << ".  Elapsed time " 
             << timer.getElapsedSeconds() << "s." << endl;
        ++depth;
      }

      // Visit the node.
      if (curNode.parent)
      {
        string move = moveStore.getMove(curNode.moveInd);
        moveStore.getMoveFunc(move)();
        ++visited;

        if (visited % 1000 == 0)
          cout << "Visited " << visited << " nodes." << endl;
      }

      if (goal.isSatisfied(cube))
      {
        // Build the list of moves by traversing up to the root node.
        node moveNode = curNode;
        cout << "Goal was satisfied." << endl;

        while (moveNode.parent)
        {
          moves.push_back(moveStore.getMove(moveNode.moveInd));
          moveNode = *moveNode.parent;
        }

        // The moves are in reverse order.  Fix that.
        reverse(moves.begin(), moves.end());
        return moves;
      }

      for (uint16_t moveInd = 0; moveInd < numMoves; ++moveInd)
      {
        // Make the move and see if the cube state has been indexed at an
        // earlier depth.
        string move = moveStore.getMove(moveInd);
        moveStore.getMoveFunc(move)();

        // If the goal is indexed, it means it's a new state and needs to be
        // visited.
        if (goal.index(cube, curNode.depth + 1))
          moveQueue.push({moveInd, &curNode, (uint8_t)(curNode.depth + 1)});

        moveStore.getInverseMoveFunc(move)();
      }

      // Undo the current node's move.
      if (curNode.parent)
      {
        string move = moveStore.getMove(curNode.moveInd);
        moveStore.getInverseMoveFunc(move)();
      }
    }

    cout << "Bad return." << endl;
    cout << "Visited " << visited << " nodes." << endl;
    return moves;
  }
}

