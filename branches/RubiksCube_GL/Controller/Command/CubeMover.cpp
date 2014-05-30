#include "CubeMover.h"

namespace busybin
{
  /**
   * Init.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, used to get the current width/heigth.
   */
  CubeMover::CubeMover(World* pWorld, WorldWindow* pWorldWnd) : Command(pWorld, pWorldWnd)

  {
    // Listen for frame buffer resize events.
    pWorldWnd->onKeypress(bind(&CubeMover::onKeypress, ref(*this), _1, _2, _3, _4));

    this->pCube = dynamic_cast<RubiksCube*>(&pWorld->at("RubiksCube"));
  }

  /**
   * Fires when a key is pressed
   * @param window The window (same as this->pWindow).
   * @param key The key code.
   * @param scancode The platform-dependent scan code of the key.
   * @param action GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT.
   * @param mods Modifiers like alt.
   */
  void CubeMover::onKeypress(int key, int scancode, int action, int mods)
  {
    if (action != GLFW_PRESS)
      return;

    switch (key)
    {
      // Rotate the whole cube left.
      case GLFW_KEY_LEFT:
        this->pCube->rotateLeft();
        break;
      // Rotate the whole cube right.
      case GLFW_KEY_RIGHT:
        this->pCube->rotateRight();
        break;
      // Rotate the whole cube down.
      case GLFW_KEY_DOWN:
        this->pCube->rotateDown();
        break;
      // Rotate the whole cube up.
      case GLFW_KEY_UP:
        this->pCube->rotateUp();
        break;
      default:
        break;
    }
  }
}

