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
    unsigned         maxDepth     = 0;
    unsigned         visited      = 0;
    unsigned         maxQueueSize = 0;
    queue<nodePtr_t> moveQueue;
    shared_ptr<Node> pCurNode;
    AutoTimer        timer;
    vector<string>   moves;

    // The corner database may be pre-populated from a file.
    if (goal.isSatisfied(cube))
      return moves;

    // The search starts at the root node.  It takes no moves to get there.
    // Each node (state of the cube) in the queue is a shared_ptr.  When nodes
    // are dequeued, they need to remain in scope memory because each node has
    // a pointer to its parent.  Nodes can only be destructed if they have 0
    // references (i.e. when all child states have been indexed).
    moveQueue.push(nodePtr_t(new Node({0xFF, nullptr})));
    goal.index(cube, 0);

    while (!moveQueue.empty())
    {
      // Next node in the queue.
      nodePtr_t pCurNode = moveQueue.front();
      moveQueue.pop();

      // Visit the node.
      moves.clear();
      this->moveToNode(pCurNode.get(), moveStore, moves);
      ++visited;

      if (maxDepth < moves.size())
      {
        cout << "BFS: Finished depth " << maxDepth
             << " (indexed depth " << maxDepth + 1 << ").  Elapsed time " 
             << timer.getElapsedSeconds() << "s." << endl;
        ++maxDepth;
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
          if (goal.index(cube, moves.size() + 1))
          {
            moveQueue.push(nodePtr_t(new Node({moveInd, pCurNode})));

            if (goal.isSatisfied(cube))
            {
              moves.push_back(move);

              cout << "BFS: Goal was satisfied in "
                   << moves.size() << " moves.  "
                   << "Visited " << visited << " nodes.  "
                   << "Max queue size " << maxQueueSize
                   << endl;

              for (const string& move: moves)
                cout << move << ' ';
              cout << endl;

              // Revert the cube to factory defaults.
              this->revertMoves(moveQueue.back().get(), moveStore);

              // Return the list of moves required to achieve the goal.
              return moves;
            }
          }

          moveStore.getInverseMoveFunc(move)();
        }
      }

      // Max queue size metric.
      if (moveQueue.size() > maxQueueSize)
        maxQueueSize = moveQueue.size();

      // Undo the current node's move.
      this->revertMoves(pCurNode.get(), moveStore);
    }

    throw RubiksCubeException("BFS: Goal not found, but move queue is empty.");
  }
}

