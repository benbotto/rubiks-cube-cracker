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
   * Launch a thread to initialize the pattern databases. 
   */
  void KorfCubeSolver::initialize()
  {
    CubeSolver::initialize();

    // Launch an initialization thread.
    this->setSolving(true);
    this->threadPool.addJob(bind(&KorfCubeSolver::indexDatabases, this));
  }

  /**
   * Initialize the pattern databases for corners and two edge groups.
   */
  void KorfCubeSolver::indexDatabases()
  {
    // Get a copy of the underlying RC model.
    RubiksCubeModel cubeModel = this->pCube->getRawModel();

    // The pattern databases will be created using breadth first search.
    BreadthFirstCubeSearcher bfSearcher;

    // This MoveStore holds the 18 moves for the 6 sides.
    ModelTwistStore modelTwistStore(cubeModel);

    cout << "Initializing pattern databases for KorfCubeSolver." << endl;

    // First create the corner database.
    GoalG1_CornerDatabase cornerGoal(&this->cornerDB);
    bfSearcher.findGoal(cornerGoal, cubeModel, modelTwistStore);

    this->setSolving(false);

    cout << "Korf initialization complete." << endl;
  }

  /**
   * Solve the cube.  This is run in a separate thread.
   */
  void KorfCubeSolver::solveCube()
  {
    cout << "Solving with Korf method." << endl;
  }
}

