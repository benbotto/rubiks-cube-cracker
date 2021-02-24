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
  vector<RubiksCube::MOVE> IDACubeSearcher::findGoal(Goal& goal,
    RubiksCube& cube, MoveStore& moveStore)
  {
    typedef RubiksCube::MOVE MOVE;
    typedef priority_queue<PrioritizedMove, vector<PrioritizedMove>,
      greater<PrioritizedMove> > moveQueue_t;

    // The IDA searcher uses pattern databases that were made using an index
    // model, so this searcher only works with an index model.
    RubiksCubeIndexModel& iCube     = static_cast<RubiksCubeIndexModel&>(cube);
    AutoTimer             timer;
    stack<Node>           nodeStack;
    Node                  curNode;
    array<MOVE, 50>       moves     = {(MOVE)0xFF};
    bool                  solved    = goal.isSatisfied(iCube);
    uint8_t               bound     = 0;
    const uint8_t         numMoves  = moveStore.getNumMoves();
    uint8_t               nextBound = this->pPatternDB->getNumMoves(iCube);

    cout << "IDA*: Starting at depth " << (unsigned)nextBound << '.' << endl;

    while (!solved)
    {
      if (nodeStack.empty())
      {
        if (bound != 0)
        {
          cout << "IDA*: Finished bound " << (unsigned)bound
               << ".  Elapsed time: " << timer.getElapsedSeconds() << "s."
               << endl;
        }

        // Start with the scrambled (root) node.  Depth 0, no move required.
        nodeStack.push({iCube, (MOVE)0xFF, 0});

        // If nextBound is initialized to 0 above but the cube is not solved,
        // the DB is bad.
        if (nextBound == 0)
          throw RubiksCubeException("IDA: nextBound set to 0.");

        // If the next bound is not updated then all branches were pruned.
        // This also indicates a bad DB.
        if (nextBound == 0xFF)
          throw RubiksCubeException("IDA: nextBound set to 0xFF.");

        bound     = nextBound;
        nextBound = 0xFF;
      }

      curNode = nodeStack.top();
      nodeStack.pop();

      // Keep the list of moves.  The moves end at 0xFF.
      moves.at(curNode.depth) = (MOVE)0xFF;

      if (curNode.depth != 0)
        moves[curNode.depth - 1] = curNode.move;

      if (curNode.depth == bound)
      {
        if (goal.isSatisfied(curNode.cube))
          solved = true;
      }
      else
      {
        // This is used to sort the successors by estimated moves.
        moveQueue_t successors;

        for (uint8_t i = 0; i < numMoves; ++i)
        {
          MOVE move = moveStore.getMove(i);

          if (curNode.depth == 0 || !this->pruner.prune(move, curNode.move))
          {
            RubiksCubeIndexModel cubeCopy(curNode.cube);

            cubeCopy.move(move);

            uint8_t estSuccMoves = curNode.depth + 1 + this->pPatternDB->getNumMovesEx(
              cubeCopy, bound, curNode.depth + 1);

            if (estSuccMoves <= bound)
            {
              // If the twisted cube is estimated to take fewer move than the
              // current bound, push it, otherwise it's pruned.
              successors.push({cubeCopy, move, estSuccMoves});
            }
            else if (estSuccMoves < nextBound)
            {
              // The next bound is the minimum of all successor node moves that's
              // greater than the current bound.
              nextBound = estSuccMoves;
            }
          }
        }

        while (!successors.empty())
        {
          // Push the nodes in sorted order.
          nodeStack.push({
            successors.top().cube,
            successors.top().move,
            (uint8_t)(curNode.depth + 1)
          });

          successors.pop();
        }
      }
    }

    cout << "IDA*: Goal reached in " << timer.getElapsedSeconds() << "s."
         << endl;

    // Convert the move to a vector.
    vector<MOVE> moveVec;

    for (unsigned i = 0; i < moves.size() && (uint8_t)moves.at(i) != 0xFF; ++i)
      moveVec.push_back(moves.at(i));

    return moveVec;
  }
}

