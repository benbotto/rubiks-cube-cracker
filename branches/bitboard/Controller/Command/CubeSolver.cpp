#include "CubeSolver.h"

namespace busybin
{
  /**
   * Init.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, used to get the current width/heigth.
   * @param pMover Pointer to the CubeMover command.
   */
  CubeSolver::CubeSolver(World* pWorld, WorldWindow* pWorldWnd, CubeMover* pMover) :
    Command(pWorld, pWorldWnd),
    threadPool(1),
    pCube(dynamic_cast<RubiksCube*>(&this->getWorld()->at("RubiksCube"))),
    cubeTwistStore(*this->pCube), cubeRotStore(*this->pCube),
    solving(false), movesInQueue(false), moveTimer(false)
  {
    // Store the mover of enabling/disabling movement.
    this->pMover = pMover;

    // Listen for keypress events.
    pWorldWnd->onKeypress(bind(&CubeSolver::onKeypress, this, _1, _2, _3, _4));

    // Listen for pulse events.
    pWorldWnd->onPulse(bind(&CubeSolver::onPulse, this, _1));
  }

  /**
   * Fires when a key is pressed
   * @param window The window (same as this->pWindow).
   * @param key The key code.
   * @param scancode The platform-dependent scan code of the key.
   * @param action GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT.
   * @param mods Modifiers like alt.
   */
  void CubeSolver::onKeypress(int key, int scancode, int action, int mods)
  {
    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE && !this->solving)
    {
      this->solving = true;
      this->pMover->disable();

      // Get a copy of the underlying RC model.
      this->cubeModel = this->pCube->getRawModel();

      // Fire off a thread to solve the cube.
      this->threadPool.addJob(bind(&CubeSolver::solveCube, this));
    }
  }

  /**
   * Check if there are queued up moves on pulse and render them as needed.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void CubeSolver::onPulse(double elapsed)
  {
    // If there is a move in the queue and the move timer isn't running
    // (1 second is taken between moves to allow for animation).
    if (this->movesInQueue && 
      (!this->moveTimer.isStarted() || this->moveTimer.getElapsedSeconds() >= 1))
    {
      lock_guard<mutex> threadLock(this->moveMutex);
      string move = this->moveQueue.front();
      this->moveQueue.pop();

      // Apply the next move.  It could be a twist or a rotation.
      if (this->cubeTwistStore.isValidMove(move))
        this->cubeTwistStore.getMoveFunc(move)();
      else
        this->cubeRotStore.getMoveFunc(move)();


      // Flag whether or not there are more moves for the next run.
      this->movesInQueue = !this->moveQueue.empty();

      // Restart the timer.
      this->moveTimer.restart();
    }

    // If solving is done and the queue is empty re-enable moves.
    if (!solving && !this->movesInQueue)
      this->pMover->enable();
  }

  /**
   * Solve the cube.  This is run in a separate thread.
   */
  void CubeSolver::solveCube()
  {
    RubiksCubeView             cubeView;
    CubeSearcher               searcher;
    vector<string>             allMoves;
    vector<string>             goalMoves;
    ModelTwistStore            mdlTwistStore(this->cubeModel);
    ModelG1TwistStore          mdlG1TwistStore(this->cubeModel);
    ModelRotationStore         mdlRotStore(this->cubeModel);
    vector<GoalAndMoveStore>   goals;

    // Create the goals.
    goals.push_back({unique_ptr<Goal>(new OrientG0()),            &mdlRotStore});
    goals.push_back({unique_ptr<Goal>(new GoalG0_orient_edges()), &mdlTwistStore});
    goals.push_back({unique_ptr<Goal>(new GoalG1_G2()),           &mdlG1TwistStore});

    // Display the intial cube model.
    cout << "Initial cube state." << endl;
    cubeView.render(this->cubeModel);
    cout << "Need to achieve " << goals.size() << " goals." << endl;

    for (unsigned i = 0; i < goals.size(); ++i)
    {
      // Find the goal.
      goalMoves = searcher.findGoal(*goals[i].pGoal, this->cubeModel, *goals[i].pMoveStore);
      this->processGoalMoves(*goals[i].pGoal, *goals[i].pMoveStore, i + 1, allMoves, goalMoves);
    }

    // Print the moves.
    cout << "\n\nSolved the cube in " << allMoves.size() << " moves.\n";

    for (string move : allMoves)
      cout << move << ' ';
    cout << endl;

    // Display the cube model.
    cout << "Resulting cube.\n";
    cubeView.render(this->cubeModel);

    // Done solving - re-enable movement.
    this->solving = false;
  }

  /**
   * Helper function to process moves after a goal is achived.
   * @param goal The goal for verbosity.
   * @param moveStore The MoveStore for processing the moves
   *        in the RC model copy.
   * @param goalNum The goal number for verbosity.
   * @param allMoves This vector holds all the moves thus far.  The
   *        goalMoves vector will be appended to it.
   * @param goalMoves This vector holds the moves required to achieve
   *        the goal.  These moves will be queued for the GL cube to
   *        display, then the vector will be cleared.
   */
  void CubeSolver::processGoalMoves(const Goal& goal, MoveStore& moveStore,
    unsigned goalNum, vector<string>& allMoves, vector<string>& goalMoves)
  {
    cout << "Found goal " << goalNum << ": " << goal.getDescription() << '\n' << endl;

    // Add goalMoves to the end of allMoves.
    allMoves.insert(allMoves.end(), goalMoves.begin(), goalMoves.end());

    for (string move : goalMoves)
    {
      // Lock the move mutex so that onPulse doesn't simultaneously mangle
      // the move queue.
      lock_guard<mutex> threadLock(this->moveMutex);

      // The RC model needs to be kept in sync as it is a copy
      // of the actual RC model.
      moveStore.getMoveFunc(move)();

      // Queue this move for the GL cube to render.
      this->moveQueue.push(move);
      this->movesInQueue = true;
    }

    // Clear the vector for the next goal.
    goalMoves.clear();
  }
}

