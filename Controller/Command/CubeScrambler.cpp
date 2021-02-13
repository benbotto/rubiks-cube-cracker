#include "CubeScrambler.h"
#include <functional>
using std::bind;
using std::ref;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;

namespace busybin
{
  /**
   * Init, storing a reference to the cube.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, for binding keypress events.
   * @param pMover Pointer to the a CubeMover instance, which is used to apply
   * the scramble moves.
   */
  CubeScrambler::CubeScrambler(World* pWorld, WorldWindow* pWorldWnd, CubeMover* pMover) : 
    Command(pWorld, pWorldWnd),
    pMover(pMover)
  {
    // Listen for keypress events.
    pWorldWnd->onKeypress(bind(&CubeScrambler::onKeypress, ref(*this), _1, _2, _3, _4));

    this->pCube = dynamic_cast<RubiksCubeWorldObject*>(&pWorld->at("RubiksCube"));
  }

  /**
   * Fires when a key is pressed and scrambles the cube.
   * @param key The key code.
   * @param scancode The platform-dependent scan code of the key.
   * @param action GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT.
   * @param mods Modifiers like alt.
   */
  void CubeScrambler::onKeypress(int key, int scancode, int action, int mods)
  {
    // On F5 press, and if movement is enabled (e.g. not solving or
    // initializing).
    if (key == GLFW_KEY_F5 && action == GLFW_PRESS && this->pMover->isEnabled())
    {
      typedef RubiksCube::MOVE MOVE;

      const unsigned SCRAMBLE_SIZE = 100;

      MovePruner      pruner;
      vector<MOVE>    moves;
      RubiksCubeModel cube = this->pCube->getRawModel();
      TwistStore      twistStore(cube);
      Random          rand(0, twistStore.getNumMoves() - 1);

      moves.reserve(SCRAMBLE_SIZE);
      moves.push_back(twistStore.getMove(rand.next()));

      while (moves.size() < SCRAMBLE_SIZE)
      {
        MOVE move = twistStore.getMove(rand.next());

        if (!pruner.prune(moves.back(), move))
          moves.push_back(move);
      }

      cout << "Scramble: ";
      cout << setfill(' ');

      for (unsigned i = 0; i < moves.size(); ++i)
      {
        if (i % 10 == 0)
          cout << '\n';

        cout << setw(3) << left << this->pCube->getMove(moves.at(i));
      }
      cout << endl;

      for (const MOVE move : moves)
        this->pCube->move(move);
    }
  }
}

