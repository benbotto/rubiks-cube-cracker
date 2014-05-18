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
    GASolver       solver(10, 300, 40, cube);

    // Let the user scramble the cube.
    scrambler.manualScramble();

    // Solve the cube.
    solver.solve();
  }
}

