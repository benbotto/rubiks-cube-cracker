#include "BreadthFirstCubeSearcher.h"

namespace busybin
{
  /**
   * Apply the moves needed to get to node by traversing from the root node
   * down to node.
   */
  void BreadthFirstCubeSearcher::moveToNode(const Node* pNode,
    MoveStore& moveStore, vector<string>& moves) const
  {
    stack<uint8_t> moveStack;

    while (pNode->pParent)
    {
      moveStack.push(pNode->moveInd);
      pNode = pNode->pParent.get();
    }

    while (!moveStack.empty())
    {
      string move = moveStore.getMove(moveStack.top());
      moves.push_back(move);

      moveStack.pop();
      moveStore.getMoveFunc(move)();
    }
  }

  /**
   * Revert all moves starting with node's move until the root node.
   */
  void BreadthFirstCubeSearcher::revertMoves(const Node* pNode, MoveStore& moveStore) const
  {
    while (pNode->pParent)
    {
      string move = moveStore.getMove(pNode->moveInd);
      string invMove = moveStore.getInverseMove(move);
      moveStore.getInverseMoveFunc(move)();
      pNode = pNode->pParent.get();
    }
  }

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
    uint8_t          numMoves     = moveStore.getNumMoves();
    uint8_t          depth        = 0;
    unsigned         visited      = 0;
    unsigned         maxQueueSize = 0;
    unsigned         maxIndDepth  = 0;
    queue<nodePtr_t> moveQueue;
    shared_ptr<Node> pCurNode;
    AutoTimer        timer;
    vector<string>   moves;

    // The corner database may be pre-populated from a file.
    if (goal.isSatisfied(cube))
      return moves;

    // The search starts at the root node.  It takes no moves to get there.
    //moveQueue.push({0xFF, nullptr, depth});
    moveQueue.push(nodePtr_t(new Node({0xFF, nullptr, depth})));
    goal.index(cube, depth);

    while (!moveQueue.empty())
    {
      // Next node in the queue.
      nodePtr_t pCurNode = moveQueue.front();
      moveQueue.pop();

      if (depth < pCurNode->depth)
      {
        cout << "BFS: Finished depth " << (unsigned)depth << ".  Elapsed time " 
             << timer.getElapsedSeconds() << "s." << endl;
        ++depth;
      }

      // Visit the node.
      moves.clear();
      this->moveToNode(pCurNode.get(), moveStore, moves);
      ++visited;

      if (goal.isSatisfied(cube))
      {
        cout << "Goal was satisfied: ";

        for (const string& move: moves)
          cout << move << ' ';
        cout << endl;

        cout << "Visited " << visited << " nodes." << endl;
        cout << "Max queue size " << maxQueueSize << endl;
        cout << "Max num moves " << maxIndDepth << endl;

        // Revert back to the original state.
        this->revertMoves(pCurNode.get(), moveStore);

        // Return the list of moves required to achieve the goal.
        return moves;
      }

      for (uint8_t moveInd = 0; moveInd < numMoves; ++moveInd)
      {
        string move = moveStore.getMove(moveInd);

        if (!this->prune(move, moves))
        {
          // Make the move and see if the cube state has been indexed at an
          // earlier depth.
          moveStore.getMoveFunc(move)();

          // If the goal is indexed, it means it's a new state and needs to be
          // visited.
          if (goal.index(cube, pCurNode->depth + 1))
            moveQueue.push(nodePtr_t(new Node({moveInd, pCurNode, (uint8_t)(pCurNode->depth + 1)})));

          moveStore.getInverseMoveFunc(move)();
        }
      }

      // Max queue size metric.
      if (moveQueue.size() > maxQueueSize)
        maxQueueSize = moveQueue.size();

      // Max number of moves.
      if ((unsigned)(pCurNode->depth + 1) > maxIndDepth)
        maxIndDepth = pCurNode->depth + 1;

      // Undo the current node's move.
      this->revertMoves(pCurNode.get(), moveStore);
    }

    cout << "Bad return." << endl;
    cout << "Visited " << visited << " nodes." << endl;
    return moves;
  }
}

