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
    CubeSolver(pWorld, pWorldWnd, pMover, pThreadPool, GLFW_KEY_F1),
    g1DB(),
    g2DB()
  {
  }

  /**
   * Launch a thread to initialize the pattern databases.
   */
  void ThistlethwaiteCubeSolver::initialize()
  {
    CubeSolver::initialize();

    // Launch an initialization thread.
    cout << "Initializing pattern databases for ThistlethwaiteCubeSolver." << endl;

    // Index each pattern database.
    this->pThreadPool->addJob(bind(&ThistlethwaiteCubeSolver::indexG1Database, this));
    this->pThreadPool->addJob(bind(&ThistlethwaiteCubeSolver::indexG2Database, this));
  }

  /**
   * Initialize the pattern database for G0->G1.
   */
  void ThistlethwaiteCubeSolver::indexG1Database()
  {
    string fileName = "./Data/thistlethwiateG1.pdb";

    if (!this->g1DB.fromFile(fileName))
    {
      // An index model is used for building pattern databases since it stores
      // the orientations directly.
      RubiksCubeIndexModel iCube;

      // A specialized IDDFS search is used to index the group databases.
      GroupPatternDatabaseIndexer indexer;

      // The goal is to index all the G1 database.  It will hold the shortest
      // number of moves from any edge orientation to the nearest G1 state (all
      // edges oriented).
      G1DatabaseGoal goal(&this->g1DB);

      // The group goal is G1: all edges oriented.
      GoalG0_G1 groupGoal;

      // Database for keeping track of "seen" states.
      G1PatternDatabase seenDB;

      // All 18 twists can be used for moving from G0->G1.
      TwistStore twistStore(iCube);

      this->setSolving(true);

      cout << "Goal 1:\n"
           << "  " << goal.getDescription() << '\n'
           << "  Group goal: " << groupGoal.getDescription() << endl;

      indexer.findGoal(goal, groupGoal, iCube, seenDB, twistStore);

      this->g1DB.toFile(fileName);

      this->setSolving(false);
    }
  }

  /**
   * Initialize the pattern database for G1->G2.
   */
  void ThistlethwaiteCubeSolver::indexG2Database()
  {
    string fileName = "./Data/thistlethwiateG2.pdb";

    if (!this->g2DB.fromFile(fileName))
    {
      // See indexG1Database for notes.
      RubiksCubeIndexModel        iCube;
      GroupPatternDatabaseIndexer indexer;
      G2DatabaseGoal              goal(&this->g2DB);
      G2PatternDatabase           seenDB;

      // The group goal is G2: all corners oriented, and all M-slice edges in
      // the M slice (UF, UB, DF, DB).
      GoalG1_G2 groupGoal;

      // Quarter turns of F and B are excluded (16 moves).
      G1TwistStore g1TwistStore(iCube);

      this->setSolving(true);

      cout << "Goal 2:\n"
           << "  " << goal.getDescription() << '\n'
           << "  Group goal: " << groupGoal.getDescription() << endl;

      indexer.findGoal(goal, groupGoal, iCube, seenDB, g1TwistStore);

      this->g2DB.toFile(fileName);

      this->setSolving(false);
    }
  }

  /**
   * Solve the cube.  This is run in a separate thread.
   */
  void ThistlethwaiteCubeSolver::solveCube()
  {
    RubiksCubeModel stdCube = this->pCube->getRawModel();
    RubiksCubeView  cubeView;
    vector<MOVE>    allMoves;
    vector<MOVE>    goalMoves;

    cout << "Solving with Thistlethwaite method." << endl;

    cout << "Initial cube state." << endl;
    cubeView.render(*this->pCube);

    // First goal: orient the cube with red up and white front.
    {
      BreadthFirstCubeSearcher bfsSearcher;
      OrientGoal               orientGoal;
      RotationStore            rotStore(stdCube);

      goalMoves = bfsSearcher.findGoal(orientGoal, stdCube, rotStore);

      this->processGoalMoves(orientGoal, stdCube, 1, allMoves, goalMoves);
    }

    // The remaining goals use the index model.  (The cube must be oriented
    // correctly to be converted to an index model.)
    RubiksCubeIndexModel iCube(stdCube);

    // Second goal: Orient all edges (G1).
    {
      IDACubeSearcher idaSearcher(&this->g1DB);
      GoalG0_G1       g1Goal;
      TwistStore      twistStore(iCube);

      goalMoves = idaSearcher.findGoal(g1Goal, iCube, twistStore);
      this->processGoalMoves(g1Goal, iCube, 2, allMoves, goalMoves);
    }

    // Third goal: Orient all corners and position M slice edges.
    // Excludes quarter turns of F and B.
    {
      IDACubeSearcher idaSearcher(&this->g2DB);
      GoalG1_G2       g2Goal;
      G1TwistStore    g1TwistStore(iCube);

      goalMoves = idaSearcher.findGoal(g2Goal, iCube, g1TwistStore);
      this->processGoalMoves(g2Goal, iCube, 3, allMoves, goalMoves);
    }

    cout << "\n\nSolved the cube in " << allMoves.size() << " moves.\n";

    // Convert the moves to strings and print them.
    vector<string> allMoveStrings;

    for (MOVE move : allMoves)
      allMoveStrings.push_back(this->pCube->getMove(move));

    for (string move : allMoveStrings)
      cout << move << ' ';
    cout << endl;

    // Simplify the moves if posible.
    vector<string> simpMoves = this->simplifyMoves(allMoveStrings);

    cout << "Simplified to " << simpMoves.size() << " moves.\n";
    for (string move : simpMoves)
      cout << move << ' ';
    cout << endl;

    // Display the cube model.
    cout << "Resulting cube.\n";
    cubeView.render(iCube);

    cout << "Edge orientations.\n";
    for (uint8_t i = 0; i < 12; ++i)
      cout << (unsigned)iCube.getEdgeOrientation((RubiksCubeIndexModel::EDGE)i) << ' ';
    cout << endl;

    cout << "Corner orientations.\n";
    for (uint8_t i = 0; i < 8; ++i)
      cout << (unsigned)iCube.getCornerOrientation((RubiksCubeIndexModel::CORNER)i) << ' ';
    cout << endl;

    // Done solving - re-enable movement.  (Note that solving is set to true in
    // the parent class on keypress.)
    this->setSolving(false);
  }
}

