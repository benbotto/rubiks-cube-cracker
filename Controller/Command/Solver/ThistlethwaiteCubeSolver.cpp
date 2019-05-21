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
    G3TwistStore g3TwistStore(cubeModel);

    // Generate all corner permutations that can be reached from the solved state
    // using only double twists.  These are stored in this->g3Perms, and used
    // by Group 2 goals.
    cout << "Initializing pattern databases for ThistlethwaiteCubeSolver." << endl;

    this->setSolving(true);

    this->searcher.findGoal(this->g3Perms, cubeModel, g3TwistStore);
    this->setSolving(false);

    cout << "Thistlethwaite initialization complete." << endl;
  }

  /**
   * Solve the cube.  This is run in a separate thread.
   */
  void ThistlethwaiteCubeSolver::solveCube()
  {
    RubiksCubeView           cubeView;
    vector<MOVE>             allMoves;
    vector<MOVE>             goalMoves;
    vector<string>           allMoveStrings;
    vector<string>           simpMoves;
    RubiksCubeModel          cubeModel = this->pCube->getRawModel();
    TwistStore               twistStore(cubeModel);
    G1TwistStore             g1TwistStore(cubeModel);
    G2TwistStore             g2TwistStore(cubeModel);
    G3TwistStore             g3TwistStore(cubeModel);
    RotationStore            rotStore(cubeModel);
    vector<GoalAndMoveStore> goals;

    // Create the goals.
    goals.push_back({unique_ptr<Goal>(new OrientGoal()),                     &rotStore});
    goals.push_back({unique_ptr<Goal>(new GoalG0_G1()),                      &twistStore});
    goals.push_back({unique_ptr<Goal>(new GoalG1_G2()),                      &g1TwistStore});
    goals.push_back({unique_ptr<Goal>(new GoalG2_G3_Corners(this->g3Perms)), &g2TwistStore});
    goals.push_back({unique_ptr<Goal>(new GoalG2_G3_Edges(this->g3Perms)),   &g2TwistStore});
    goals.push_back({unique_ptr<Goal>(new SolveGoal()),                      &g3TwistStore});

    // Display the intial cube model.
    cout << "Initial cube state." << endl;
    cubeView.render(cubeModel);
    cout << "Need to achieve " << goals.size() << " goals." << endl;

    for (unsigned i = 0; i < goals.size(); ++i)
    {
      // Find the goal.
      goalMoves = this->searcher.findGoal(*goals[i].pGoal, cubeModel, *goals[i].pMoveStore);
      this->processGoalMoves(*goals[i].pGoal, cubeModel, i + 1, allMoves, goalMoves);
    }

    // Print the moves.
    cout << "\n\nSolved the cube in " << allMoves.size() << " moves.\n";

    // Convert the moves to strings.
    for (MOVE move : allMoves)
      allMoveStrings.push_back(this->pCube->getMove(move));

    for (string move : allMoveStrings)
      cout << move << ' ';
    cout << endl;

    // Simplify the moves if posible.
    simpMoves = this->simplifyMoves(allMoveStrings);
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

