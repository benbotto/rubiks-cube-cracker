#include "CubeSolver.h"

namespace busybin
{
  /**
   * Init.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, used to bind key and pulse events.
   * @param pMover Pointer to the CubeMover command.
   * @param solveKey The GLFW key that triggers the solver to start.
   */
  CubeSolver::CubeSolver(World* pWorld, WorldWindow* pWorldWnd,
    CubeMover* pMover, int solveKey) :
    Command(pWorld, pWorldWnd),
    cubeTwistStore(*this->pCube),
    cubeRotStore(*this->pCube),
    solving(false),
    movesInQueue(false),
    moveTimer(false),
    solveKey(solveKey),
    threadPool(1),
    pCube(dynamic_cast<RubiksCube*>(&this->getWorld()->at("RubiksCube")))
  {
    // Store the mover for enabling/disabling movement.  Movement of the cube
    // is disabled while the cube is being solved.
    this->pMover = pMover;
  }

  /**
   * This can be overridden in sub classes and gives solvers the chance to
   * initialize pattern databases and such (whatever's needed for the solver).
   * It's launched in a thread.
   */
  void CubeSolver::initialize()
  {
    // Listen for keypress events and start the solve when solveKey is pressed.
    this->getWorldWindow()->onKeypress(bind(&CubeSolver::onKeypress, this, _1, _2, _3, _4));

    // Listen for pulse events and apply solution moves.
    this->getWorldWindow()->onPulse(bind(&CubeSolver::onPulse, this, _1));
  }

  /**
   * Fires when a key is pressed.
   * @param window The window (same as this->pWindow).
   * @param key The key code.
   * @param scancode The platform-dependent scan code of the key.
   * @param action GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT.
   * @param mods Modifiers like alt.
   */
  void CubeSolver::onKeypress(int key, int scancode, int action, int mods)
  {
    // See the setSolving method, which disables cube movement during a solve.
    // The mover could be disabled from any solver.
    if (action == GLFW_PRESS && key == this->solveKey && this->pMover->isEnabled())
    {
      this->setSolving(true);

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
   * Put the cube in a "solving" state, which disables cube movement.
   * @param solving Whether or not the cube is being solved.  When so, cube movement
   *        is disabled.
   */
  void CubeSolver::setSolving(bool solving)
  {
    this->solving = solving;

    if (this->solving)
      this->pMover->disable();
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

  /**
   * Reduce moves.  For example, L2 L2 can be removed.  L L L is the same as L'.
   * etc.
   * @param moves The set of moves required to solve the cube.
   */
  vector<string> CubeSolver::simplifyMoves(const vector<string>& moves) const
  {
    string        movesStr = "";
    istringstream stream;

    for (string move : moves)
      movesStr += move + " ";

    this->replace("U2 U2 ", movesStr, " ");
    this->replace("L2 L2 ", movesStr, " ");
    this->replace("F2 F2 ", movesStr, " ");
    this->replace("R2 R2 ", movesStr, " ");
    this->replace("B2 B2 ", movesStr, " ");
    this->replace("D2 D2 ", movesStr, " ");

    this->replace("U U' ", movesStr, " ");
    this->replace("L L' ", movesStr, " ");
    this->replace("F F' ", movesStr, " ");
    this->replace("R R' ", movesStr, " ");
    this->replace("B B' ", movesStr, " ");
    this->replace("D D' ", movesStr, " ");

    this->replace("U' U ", movesStr, " ");
    this->replace("L' L ", movesStr, " ");
    this->replace("F' F ", movesStr, " ");
    this->replace("R' R ", movesStr, " ");
    this->replace("B' B ", movesStr, " ");
    this->replace("D' D ", movesStr, " ");

    this->replace("U U U ", movesStr, "U' ");
    this->replace("L L L ", movesStr, "L' ");
    this->replace("F F F ", movesStr, "F' ");
    this->replace("R R R ", movesStr, "R' ");
    this->replace("B B B ", movesStr, "B' ");
    this->replace("B B B ", movesStr, "B' ");

    this->replace("U U ", movesStr, "U2 ");
    this->replace("L L ", movesStr, "L2 ");
    this->replace("F F ", movesStr, "F2 ");
    this->replace("R R ", movesStr, "R2 ");
    this->replace("B B ", movesStr, "B2 ");
    this->replace("D D ", movesStr, "D2 ");

    // Copy the moves back to a vector.
    stream.str(movesStr);
    return vector<string>(istream_iterator<string>(stream), istream_iterator<string>());
  }

  /**
   * Helper for replacing in a string.
   * @param needle What to replace,
   * @param haystack Where to search for needle.
   * @param with What to replace needle with.
   */
  void CubeSolver::replace(const string& needle, string& haystack, const string& with) const
  {
    string::size_type pos;

    while ((pos = haystack.find(needle)) != string::npos)
    {
      cout << "Found " << needle << " in " << haystack << " at position " << pos
           << ".  Replacing with " << with << '.' << endl;
      haystack.replace(pos, needle.length(), with);
    }
  }
}

