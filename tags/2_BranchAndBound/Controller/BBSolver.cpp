#include "BBSolver.h"

namespace busybin
{
  /**
   * Initialize the solver.
   * @param cube The cube (must remain in scope).
   */
  BBSolver::BBSolver(RubiksCube& cube) : pCube(&cube),
    moveStore(cube), maxDepth(4)
  {
  }

  /**
   * Solve the cube and return the list of moves.
   */
  vector<string> BBSolver::solve()
  {
    set<string>    cubeStates;
    vector<string> moves;
    bool           solved = false;

    while (!solved)
    {
      unsigned absoluteBestFit = 0;
      unsigned bestFit = 0;
      string   bestMove;
      string   bestCubeState;
      string   cubeState;

      for (unsigned i = 0; i < this->moveStore.getNumMoves() && !solved; ++i)
      {
        string   move = this->moveStore.getMove(i);
        unsigned fitness;

        // Apply the move.
        this->moveStore.getMoveFunc(move)();

        cubeState = this->cubeToString();

        // Don't go back to a previous state.
        if (!cubeStates.count(cubeState))
        {
          // Store the state.
          cubeStates.insert(cubeState);

          // Get the max fitness for this move branch.
          fitness = this->max(0, cubeStates);

          // Retract the state.
          cubeStates.erase(cubeState);

          // Store the new best if needed (gte because there may not 
          // be a move better than 0).
          if (fitness >= bestFit)
          {
            bestFit       = fitness;
            bestMove      = move;
            bestCubeState = cubeState;
          }

          // Best ever achieved fitness.
          if (fitness > absoluteBestFit)
            absoluteBestFit = fitness;

          if (this->evaluator.eval(*this->pCube) == 100)
            solved = true;
        }

        // Revert the move.
        this->moveStore.getInverseMoveFunc(move)();
      }

      // Store the best move, and apply it.
      moves.push_back(bestMove);
      cubeStates.insert(bestCubeState);
      this->moveStore.getMoveFunc(bestMove)();
      
      // Show the move and the cube.
      cout << "Best move found to be " << bestMove << " with fitness " 
           << bestFit << ".  Best fitness achived so far is "
           << absoluteBestFit << "." << endl;

      this->cubeView.render(*this->pCube);
    }

    // TODO: unwind.

    return moves;
  }

  /**
   * Return the max move.
   * @param depth The current depth of the search.
   * @param cubeStates A set of all cube states that have been visited.
   */
  unsigned BBSolver::max(unsigned depth, set<string>& cubeStates)
  {
    unsigned bestFit = 0;
    string   cubeState;

    // Evaluate the cube at max depth.
    if (depth == this->maxDepth)
      return this->evaluator.eval(*this->pCube);

    for (unsigned i = 0; i < this->moveStore.getNumMoves(); ++i)
    {
      string   move = this->moveStore.getMove(i);
      unsigned fitness;

      // Apply the move.
      this->moveStore.getMoveFunc(move)();

      cubeState = this->cubeToString();

      // Don't go back to a previous state.
      if (!cubeStates.count(cubeState))
      {
        // Store the state.
        cubeStates.insert(cubeState);

        // Get the max fitness for this move branch.
        fitness = this->max(depth + 1, cubeStates);

        // Retract the state.
        cubeStates.erase(cubeState);

        // Store the new best if needed (gte because there may not 
        // be a move better than 0).
        if (fitness >= bestFit)
          bestFit  = fitness;
      }

      // Revert the move.
      this->moveStore.getInverseMoveFunc(move)();
    }

    return bestFit;
  }

  /**
   * Convert the cube to a string.
   */
  string BBSolver::cubeToString() const
  {
    string c;

    for (unsigned i = 0; i < 54; ++i)
      c += (char)this->pCube->get(i);

    return c;
  }
}

