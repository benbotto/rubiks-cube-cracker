#include "ThistlethwaiteCubeSolver.h"

namespace busybin
{
  /**
   * Init.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, used to bind key and pulse events.
   * @param pMover Pointer to the CubeMover command.
   * @param pThreadPool A ThreadPool pointer for queueing jobs.
   */
  ThistlethwaiteCubeSolver::ThistlethwaiteCubeSolver(World* pWorld,
    WorldWindow* pWorldWnd, CubeMover* pMover, ThreadPool* pThreadPool) :
    CubeSolver(pWorld, pWorldWnd, pMover, pThreadPool, GLFW_KEY_F1)
  {
  }

  /**
   * Launch a thread to initialize the pattern database.
   */
  void ThistlethwaiteCubeSolver::initialize()
  {
    CubeSolver::initialize();

    // Launch an initialization thread.
    this->setSolving(true);
    this->pThreadPool->addJob(bind(&ThistlethwaiteCubeSolver::indexDatabase, this));
  }

  /**
   * Initialize the pattern databases for the third set of goals.
   */
  void ThistlethwaiteCubeSolver::indexDatabase()
  {
    // Get a copy of the underlying RC model.
    RubiksCubeModel cubeModel = this->pCube->getRawModel();

    // This twist store contains 180-degree twists only (L2, R2, etc.).
    ModelG3TwistStore mdlG3TwistStore(cubeModel);

    // Generate all corner permutations that can be reached from the solved state
    // using only double twists.  These are stored in this->g3Perms, and used
    // by Group 2 goals.
    cout << "Initializing pattern databases for ThistlethwaiteCubeSolver." << endl;

    this->searcher.findGoal(this->g3Perms, cubeModel, mdlG3TwistStore);
    this->setSolving(false);

    cout << "Thistlethwaite initialization complete." << endl;
  }

  /**
   * Solve the cube.  This is run in a separate thread.
   */
  void ThistlethwaiteCubeSolver::solveCube()
  {
    RubiksCubeView           cubeView;
    vector<string>           allMoves;
    vector<string>           goalMoves;
    vector<string>           simpMoves;
    RubiksCubeModel          cubeModel = this->pCube->getRawModel();
    ModelTwistStore          mdlTwistStore(cubeModel);
    ModelG1TwistStore        mdlG1TwistStore(cubeModel);
    ModelG2TwistStore        mdlG2TwistStore(cubeModel);
    ModelG3TwistStore        mdlG3TwistStore(cubeModel);
    ModelRotationStore       mdlRotStore(cubeModel);
    vector<GoalAndMoveStore> goals;

    // Create the goals.
    goals.push_back({unique_ptr<Goal>(new OrientGoal()),                     &mdlRotStore});
    goals.push_back({unique_ptr<Goal>(new GoalG0_G1()),                      &mdlTwistStore});
    goals.push_back({unique_ptr<Goal>(new GoalG1_G2()),                      &mdlG1TwistStore});
    goals.push_back({unique_ptr<Goal>(new GoalG2_G3_Corners(this->g3Perms)), &mdlG2TwistStore});
    goals.push_back({unique_ptr<Goal>(new GoalG2_G3_Edges(this->g3Perms)),   &mdlG2TwistStore});
    goals.push_back({unique_ptr<Goal>(new SolveGoal()),                      &mdlG3TwistStore});

    // Display the intial cube model.
    cout << "Initial cube state." << endl;
    cubeView.render(cubeModel);
    cout << "Need to achieve " << goals.size() << " goals." << endl;

    for (unsigned i = 0; i < goals.size(); ++i)
    {
      // Find the goal.
      goalMoves = this->searcher.findGoal(*goals[i].pGoal, cubeModel, *goals[i].pMoveStore);
      this->processGoalMoves(*goals[i].pGoal, *goals[i].pMoveStore, i + 1, allMoves, goalMoves);
    }

    // Print the moves.
    cout << "\n\nSolved the cube in " << allMoves.size() << " moves.\n";

    for (string move : allMoves)
      cout << move << ' ';
    cout << endl;

    // Simplify the moves if posible.
    simpMoves = this->simplifyMoves(allMoves);
    cout << "Simplified to " << simpMoves.size() << " moves.\n";
    for (string move : simpMoves)
      cout << move << ' ';
    cout << endl;

    // Display the cube model.
    cout << "Resulting cube.\n";
    cubeView.render(cubeModel);

    // Done solving - re-enable movement.  (Note that solving is set to true in
    // the parent class on keypress.)
    this->setSolving(false);
  }
}

