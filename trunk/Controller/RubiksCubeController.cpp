#include "RubiksCubeController.h"

namespace busybin
{
  /**
   * Initialize.
   */
  RubiksCubeController::RubiksCubeController()
  {
  }

  /**
   * Main game loop.
   */
  void RubiksCubeController::start()
  {
    RubiksCube     cube;
    RubiksCubeView cubeView;
    MoveStore      moveStore(cube);
    Scrambler      scrambler(cube, moveStore, cubeView);
    CubeSearcher   searcher(cube);
    vector<string> moves;
    Goal1          goal1;
    Goal2          goal2;

    // Let the user scramble the cube.
    scrambler.manualScramble();

    // Try to achieve the goals.
    searcher.find(goal1, moves);
    searcher.find(goal2, moves);

    // Print the moves.
    for (string move : moves)
      cout << move << ' ';
    cout << endl;

    for (string move : moves)
    {
      cout << move << endl;
      moveStore.getMoveFunc(move)();
      cubeView.render(cube);
    }
  }
}

