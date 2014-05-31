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

      // Rotate the up face.
      case GLFW_KEY_U:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->uPrime();
        else
          this->pCube->u();
        break;

      // Rotate the left face.
      case GLFW_KEY_L:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->lPrime();
        else
          this->pCube->l();
        break;

      // Rotate the front face.
      case GLFW_KEY_F:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->fPrime();
        else
          this->pCube->f();
        break;

      // Rotate the right face.
      case GLFW_KEY_R:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->rPrime();
        else
          this->pCube->r();
        break;

      // Rotate the back face.
      case GLFW_KEY_B:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->bPrime();
        else
          this->pCube->b();
        break;

      // Rotate the down face.
      case GLFW_KEY_D:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->dPrime();
        else
          this->pCube->d();
        break;

      default:
        break;
    }
  }
}

