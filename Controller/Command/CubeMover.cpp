#include "CubeMover.h"

namespace busybin
{
  /**
   * Init.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, used to get the current width/heigth.
   */
  CubeMover::CubeMover(World* pWorld, WorldWindow* pWorldWnd) :
    Command(pWorld, pWorldWnd), moveEnabled(true)
  {
    // Listen for keypress events.
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
    if (action != GLFW_PRESS || !this->moveEnabled)
      return;

    switch (key)
    {
      // Rotate the whole cube left.
      case GLFW_KEY_LEFT:
        if (mods & GLFW_MOD_ALT)
          this->pCube->y2();
        else
          this->pCube->y();
        break;

      // Rotate the whole cube right.
      case GLFW_KEY_RIGHT:
        if (mods & GLFW_MOD_ALT)
          this->pCube->y2();
        else
          this->pCube->yPrime();
        break;

      // Rotate the whole cube down.
      case GLFW_KEY_DOWN:
        if (mods & GLFW_MOD_ALT)
          this->pCube->x2();
        else
          this->pCube->xPrime();
        break;

      // Rotate the whole cube up.
      case GLFW_KEY_UP:
        if (mods & GLFW_MOD_ALT)
          this->pCube->x2();
        else
          this->pCube->x();
        break;

      // Rotate the whole cube sideways.
      case GLFW_KEY_Z:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->zPrime();
        else if (mods & GLFW_MOD_ALT)
          this->pCube->z2();
        else
          this->pCube->z();
        break;

      // Rotate the up face.
      case GLFW_KEY_U:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->uPrime();
        else if (mods & GLFW_MOD_ALT)
          this->pCube->u2();
        else
          this->pCube->u();
        break;

      // Rotate the left face.
      case GLFW_KEY_L:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->lPrime();
        else if (mods & GLFW_MOD_ALT)
          this->pCube->l2();
        else
          this->pCube->l();
        break;

      // Rotate the front face.
      case GLFW_KEY_F:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->fPrime();
        else if (mods & GLFW_MOD_ALT)
          this->pCube->f2();
        else
          this->pCube->f();
        break;

      // Rotate the right face.
      case GLFW_KEY_R:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->rPrime();
        else if (mods & GLFW_MOD_ALT)
          this->pCube->r2();
        else
          this->pCube->r();
        break;

      // Rotate the back face.
      case GLFW_KEY_B:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->bPrime();
        else if (mods & GLFW_MOD_ALT)
          this->pCube->b2();
        else
          this->pCube->b();
        break;

      // Rotate the down face.
      case GLFW_KEY_D:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->dPrime();
        else if (mods & GLFW_MOD_ALT)
          this->pCube->d2();
        else
          this->pCube->d();
        break;

      // Rotate the middle slice.
      case GLFW_KEY_M:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->mPrime();
        else if (mods & GLFW_MOD_ALT)
          this->pCube->m2();
        else
          this->pCube->m();
        break;

      // Rotate the e slice.
      case GLFW_KEY_E:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->ePrime();
        else if (mods & GLFW_MOD_ALT)
          this->pCube->e2();
        else
          this->pCube->e();
        break;

      // Rotate the s slice.
      case GLFW_KEY_S:
        if (mods & GLFW_MOD_SHIFT)
          this->pCube->sPrime();
        else if (mods & GLFW_MOD_ALT)
          this->pCube->s2();
        else
          this->pCube->s();
        break;

      default:
        break;
    }
  }

  /**
   * Disable movement.
   */
  void CubeMover::disable()
  {
    this->moveEnabled = false;
  }

  /**
   * Enable movement.
   */
  void CubeMover::enable()
  {
    this->moveEnabled = true;
  }

  /**
   * Check if movement is enabled.
   */
  bool CubeMover::isEnabled() const
  {
    return this->moveEnabled;
  }
}

