#include "KorfCubeSolver.h"

namespace busybin
{
  /**
   * Init.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, used to bind key and pulse events.
   * @param pMover Pointer to the CubeMover command.
   * @param pThreadPool A ThreadPool pointer for queueing jobs.
   */
  KorfCubeSolver::KorfCubeSolver(World* pWorld, WorldWindow* pWorldWnd,
    CubeMover* pMover, ThreadPool* pThreadPool) :
    CubeSolver(pWorld, pWorldWnd, pMover, pThreadPool, GLFW_KEY_F2),
    cornerDB(),
    edgeG1DB(),
    edgeG2DB(),
    korfDB(&cornerDB, &edgeG1DB, &edgeG2DB)
  {
  }

  /**
   * Launch a thread to initialize the pattern databases. 
   */
  void KorfCubeSolver::initialize()
  {
    CubeSolver::initialize();

    // Launch an initialization thread.
    this->pThreadPool->addJob(bind(&KorfCubeSolver::indexDatabases, this));
  }

  /**
   * Initialize the pattern databases for corners and two edge groups.
   */
  void KorfCubeSolver::indexDatabases()
  {
    // The pattern databases will be created using breadth first search.
    BreadthFirstCubeSearcher bfSearcher;

    // A copy of the underlying cube model.
    RubiksCubeModel cubeModel = this->pCube->getRawModel();

    // The twist store has all 18 face twists.
    ModelTwistStore modelTwistStore(cubeModel);

    this->setSolving(true);

    cout << "Initializing pattern databases for KorfCubeSolver." << endl;

    // There are three goals, one for the corner states, one for 6 edges of the
    // cube, and one for the other 6 edges.  The searcher takes a reference to
    // the cube model and finds a goal.
    //
    // The seacher uses about 5GB of memory; the internal queue is quite large,
    // especially while indexing the corner database.
    if (!this->cornerDB.fromFile("./Data/corner.pdb"))
    {
      // First create the corner database.
      CornerDatabaseGoal cornerGoal(&this->cornerDB);

      cout << "Goal 1: " << cornerGoal.getDescription() << endl;

      bfSearcher.findGoal(cornerGoal, cubeModel, modelTwistStore);
      this->cornerDB.toFile("./Data/corner.pdb");
    }

    if (!this->edgeG1DB.fromFile("./Data/edgeG1.pdb"))
    {
      // Create the first edge database.
      EdgeDatabaseGoal edgeG1Goal(&this->edgeG1DB);

      cout << "Goal 2: " << edgeG1Goal.getDescription() << endl;

      bfSearcher.findGoal(edgeG1Goal, cubeModel, modelTwistStore);
      this->edgeG1DB.toFile("./Data/edgeG1.pdb");
    }

    if (!this->edgeG2DB.fromFile("./Data/edgeG2.pdb"))
    {
      // Create the second edge database.
      EdgeDatabaseGoal edgeG2Goal(&this->edgeG2DB);

      cout << "Goal 3: " << edgeG2Goal.getDescription() << endl;

      bfSearcher.findGoal(edgeG2Goal, cubeModel, modelTwistStore);
      this->edgeG2DB.toFile("./Data/edgeG2.pdb");
    }

    this->setSolving(false);

    cout << "Korf initialization complete." << endl;
  }

  /**
   * Solve the cube.  This is run in a separate thread.
   */
  void KorfCubeSolver::solveCube()
  {
    RubiksCubeView  cubeView;
    RubiksCubeModel cubeModel = this->pCube->getRawModel();
    vector<string>  allMoves;
    vector<string>  goalMoves;

    cout << "Solving with Korf method." << endl;

    cout << "Initial cube state." << endl;
    cubeView.render(cubeModel);

    // First goal: orient the cube with red up and white front.
    BreadthFirstCubeSearcher bfsSearcher;
    OrientGoal               orientGoal;
    ModelRotationStore       modelRotStore(cubeModel);

    goalMoves = bfsSearcher.findGoal(orientGoal, cubeModel, modelRotStore);

    this->processGoalMoves(orientGoal, modelRotStore, 1, allMoves, goalMoves);

    // Second goal: solve the cube.
    IDACubeSearcher idaSearcher(&this->korfDB);
    SolveGoal       solveGoal;
    ModelTwistStore modelTwistStore(cubeModel);

    goalMoves = idaSearcher.findGoal(solveGoal, cubeModel, modelTwistStore);
    this->processGoalMoves(solveGoal, modelTwistStore, 2, allMoves, goalMoves);

    // Print the moves.
    cout << "\n\nSolved the cube in " << allMoves.size() << " moves.\n";

    for (string move : allMoves)
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

