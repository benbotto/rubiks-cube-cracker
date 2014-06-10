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
    Command(pWorld, pWorldWnd), threadPool(1),
    cubeTwistStore(dynamic_cast<RubiksCube&>(this->getWorld()->at("RubiksCube"))),
    solving(false), movesInQueue(false), moveTimer(false)
  {
    // Store the mover of enabling/disabling movement.
    this->pMover = pMover;

    // Listen for keypress events.
    pWorldWnd->onKeypress(bind(&CubeSolver::onKeypress, this, _1, _2, _3, _4));

    // Listen for pulse events.
    pWorldWnd->onPulse(bind(&CubeSolver::onPulse, this, _1));

    // Store the cube.
    this->pCube = dynamic_cast<RubiksCube*>(&this->getWorld()->at("RubiksCube"));
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
    if (this->movesInQueue && 
      (!this->moveTimer.isStarted() || this->moveTimer.getElapsedSeconds() >= 1))
    {
      lock_guard<mutex> threadLock(this->moveMutex);
      
      // Apply the next move.
      string move = this->moveQueue.front();
      this->moveQueue.pop();
      this->cubeTwistStore.getMoveFunc(move)();

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
    RubiksCubeView  cubeView;
    ModelTwistStore modelTwistStore(this->cubeModel);
    CubeSearcher    searcher(this->cubeModel, modelTwistStore);
    vector<string>  allMoves;
    vector<string>  goalMoves;
    vector<unique_ptr<Goal> > goals;

    // Create the goals.
    goals.push_back(unique_ptr<Goal>(new Goal2x2x2()));
    goals.push_back(unique_ptr<Goal>(new Goal2x2x2_Plus_One_Edge()));
    goals.push_back(unique_ptr<Goal>(new Goal2x2x3()));
    goals.push_back(unique_ptr<Goal>(new Goal2x2x3_Plus_One_Edge_Corner()));
    goals.push_back(unique_ptr<Goal>(new Goal2_Layers_Minus_One_Corner_Edge()));

    // Display the intial cube model.
    cout << "Initial cube state." << endl;
    cubeView.render(this->cubeModel);
    cout << "Need to achieve " << goals.size() << " goals." << endl;

    for (unsigned i = 0; i < goals.size(); ++i)
    {
      // Find the goal.
      goalMoves = searcher.findGoal(*goals[i]);
      this->processGoalMoves(allMoves, goalMoves, modelTwistStore, i + 1, *goals[i]);

      // Find the orientation.  After each goal is achieved, the cube
      // may need to be reoriented.
      //goalMoves = searcher.findOrientation(*goals[i]);
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
   * @param allMoves This vector holds all the moves thus far.  The
   *        goalMoves vector will be appended to it.
   * @param goalMoves This vector holds the moves required to achieve
   *        the goal.  These moves will be queued for the GL cube to
   *        display, then the vector will be cleared.
   * @param modelMoveStore The model move store for processing the moves
   *        in the RC model copy.
   * @param goalNum The goal number for verbosity.
   * @param goal The goal for verbosity.
   */
  void CubeSolver::processGoalMoves(vector<string>& allMoves,
    vector<string>& goalMoves, MoveStore& moveStore,
    unsigned goalNum, const Goal& goal)
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

