#include "KorfCubeSolver.h"

namespace busybin
{
  /**
   * Init.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, used to bind key and pulse events.
   * @param pMover Pointer to the CubeMover command.
   */
  KorfCubeSolver::KorfCubeSolver(World* pWorld, WorldWindow* pWorldWnd,
    CubeMover* pMover) : CubeSolver(pWorld, pWorldWnd, pMover, GLFW_KEY_F2)
  {
  }

  /**
   * Solve the cube.  This is run in a separate thread.
   */
  void KorfCubeSolver::solveCube()
  {
    cout << "Solving with Korf method." << endl;
  }
}

