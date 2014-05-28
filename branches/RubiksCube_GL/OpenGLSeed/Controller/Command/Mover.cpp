#include "Mover.h"

namespace busybin
{
  /**
   * Init.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, used to get the current width/heigth.
   */
  Mover::Mover(World* pWorld, WorldWindow* pWorldWnd) : Command(pWorld, pWorldWnd)
  {
    // Listen for frame buffer resize events.
    pWorldWnd->onKeypress(bind(&Mover::onKeypress, ref(*this), _1, _2, _3, _4));

    // Listen for pulse events.
    pWorldWnd->onPulse(bind(&Mover::onPulse, ref(*this), _1));

    // Set up the key map.
    this->keys['a'] = false;
    this->keys['s'] = false;
    this->keys['w'] = false;
    this->keys['d'] = false;
    this->keys['q'] = false;
    this->keys['e'] = false;
  }

  /**
   * Fires when a key is pressed
   * @param window The window (same as this->pWindow).
   * @param key The key code.
   * @param scancode The platform-dependent scan code of the key.
   * @param action GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT.
   * @param mods Modifiers like alt.
   */
  void Mover::onKeypress(int key, int scancode, int action, int mods)
  {
    switch (key)
    {
      case GLFW_KEY_A:
        this->keys['a'] = (action != GLFW_RELEASE);
        break;
      case GLFW_KEY_S:
        this->keys['s'] = (action != GLFW_RELEASE);
        break;
      case GLFW_KEY_D:
        this->keys['d'] = (action != GLFW_RELEASE);
        break;
      case GLFW_KEY_W:
        this->keys['w'] = (action != GLFW_RELEASE);
        break;
      case GLFW_KEY_Q:
        this->keys['q'] = (action != GLFW_RELEASE);
        break;
      case GLFW_KEY_E:
        this->keys['e'] = (action != GLFW_RELEASE);
        break;
      default:
        break;
    }
  }

  /**
   * Every pulse move if the keys are down.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void Mover::onPulse(double elapsed)
  {
    // Handle the moves (up, down, left, right).
    if (this->keys['a'])
      this->getWorld()->getCamera().strafeLeft(elapsed);

    if (this->keys['s'])
      this->getWorld()->getCamera().moveBackward(elapsed);

    if (this->keys['d'])
      this->getWorld()->getCamera().strafeRight(elapsed);

    if (this->keys['w'])
      this->getWorld()->getCamera().moveForward(elapsed);

    if (this->keys['q'])
      this->getWorld()->getCamera().moveUp(elapsed);

    if (this->keys['e'])
      this->getWorld()->getCamera().moveDown(elapsed);

    // Update the matrix stack.
    this->getWorld()->getMatrixStack().topView() = this->getWorld()->getCamera().getView();
  }
}

