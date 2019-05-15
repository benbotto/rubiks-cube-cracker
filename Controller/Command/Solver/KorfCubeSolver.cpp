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
    // The pattern databases will be created using breadth first search for the
    // corners, and a specialized IDDFS for the edges.
    BreadthFirstCubeSearcher bfsSearcher;
    PatternDatabaseIndexer   indexer;

    // An index model is used for building the pattern databases.
    RubiksCubeIndexModel iCube;

    this->setSolving(true);

    cout << "Initializing pattern databases for KorfCubeSolver." << endl;

    // There are three goals, one for the corner states, one for 6 edges of the
    // cube, and one for the other 6 edges.  The searcher takes a reference to
    // the cube model and finds a goal.
    //
    // The seacher uses about 5GB of memory; the internal queue is quite large
    // while indexing the corner database.
    if (!this->cornerDB.fromFile("./Data/corner.pdb"))
    {
      // First create the corner database.
      CornerDatabaseGoal cornerGoal(&this->cornerDB);
      TwistStore         twistStore(iCube);

      cout << "Goal 1: " << cornerGoal.getDescription() << endl;

      bfsSearcher.findGoal(cornerGoal, iCube, twistStore);
      this->cornerDB.toFile("./Data/corner.pdb");
    }

    if (!this->edgeG1DB.fromFile("./Data/edgeG1.pdb"))
    {
      // Create the first edge database.
      EdgeDatabaseGoal      edgeG1Goal(&this->edgeG1DB);
      EdgeG1PatternDatabase seenDB;

      cout << "Goal 2: " << edgeG1Goal.getDescription() << endl;

      indexer.findGoal(edgeG1Goal, iCube, seenDB);
      this->edgeG1DB.toFile("./Data/edgeG1.pdb");
    }

    if (!this->edgeG2DB.fromFile("./Data/edgeG2.pdb"))
    {
      // Create the second edge database.
      EdgeDatabaseGoal      edgeG2Goal(&this->edgeG2DB);
      EdgeG2PatternDatabase seenDB;

      cout << "Goal 3: " << edgeG2Goal.getDescription() << endl;

      indexer.findGoal(edgeG2Goal, iCube, seenDB);
      this->edgeG2DB.toFile("./Data/edgeG2.pdb");
    }

    // Inflate the DB for faster access (doubles the size, but no bit-wise
    // operations are required when indexing).
    this->korfDB.inflate();

    this->setSolving(false);

    cout << "Korf initialization complete." << endl;
  }

  /**
   * Solve the cube.  This is run in a separate thread.
   */
  void KorfCubeSolver::solveCube()
  {
    RubiksCubeView cubeView;
    vector<MOVE>   allMoves;
    vector<MOVE>   goalMoves;

    cout << "Solving with Korf method." << endl;

    cout << "Initial cube state." << endl;
    cubeView.render(*this->pCube);

    // First goal: orient the cube with red up and white front.
    RubiksCubeModel          stdCube = this->pCube->getRawModel();
    BreadthFirstCubeSearcher bfsSearcher;
    OrientGoal               orientGoal;
    RotationStore            rotStore(stdCube);

    goalMoves = bfsSearcher.findGoal(orientGoal, stdCube, rotStore);

    this->processGoalMoves(orientGoal, stdCube, 1, allMoves, goalMoves);

    // Second goal: solve the cube.
    RubiksCubeIndexModel iCube(stdCube);
    IDACubeSearcher      idaSearcher(&this->korfDB);
    SolveGoal            solveGoal;
    TwistStore           twistStore(iCube);

    goalMoves = idaSearcher.findGoal(solveGoal, iCube, twistStore);
    this->processGoalMoves(solveGoal, iCube, 2, allMoves, goalMoves);

    // Print the moves.
    cout << "\n\nSolved the cube in " << allMoves.size() << " moves.\n";

    for (MOVE move : allMoves)
      cout << this->pCube->getMove(move) << ' ';
    cout << endl;

    // Display the cube model.
    cout << "Resulting cube.\n";
    cubeView.render(iCube);

    // Done solving - re-enable movement.  (Note that solving is set to true in
    // the parent class on keypress.)
    this->setSolving(false);
  }
}

