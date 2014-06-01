#include "Looker.h"

namespace busybin
{
  /**
   * Init.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, used to get the current width/heigth.
   */
  Looker::Looker(World* pWorld, WorldWindow* pWorldWnd) : Command(pWorld, pWorldWnd)
  {
    this->mouseLook = false;

    // Listen for pulse events.
    pWorldWnd->onPulse(bind(&Looker::onPulse, ref(*this), _1));

    // Listen for click events.
    pWorldWnd->onMouseButton(bind(&Looker::onMouseButton, ref(*this), _1, _2, _3));
  }

  /**
   * Every pulse move if the mouse has moved.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void Looker::onPulse(double elapsed)
  {
    if (this->mouseLook)
    {
      pair<double, double> cursorPos = this->getWorldWindow()->getCursorPos();
      int    sizeX  = this->getWorldWindow()->getWidth();
      int    sizeY  = this->getWorldWindow()->getHeight();
      int    centX  = sizeX / 2;
      int    centY  = sizeY / 2;
      double deltaX = cursorPos.first  - centX;
      double deltaY = cursorPos.second - centY;

      // Cap the deltas.
      if (deltaX >  25) deltaX =  25;
      if (deltaX < -25) deltaX = -25;
      if (deltaY >  25) deltaY =  25;
      if (deltaY < -25) deltaY = -25;

      // Yaw/pitch the camera.
      this->getWorld()->getCamera().yaw(elapsed, deltaX);
      this->getWorld()->getCamera().pitch(elapsed, deltaY);

      // Warp the cursor back to the center.
      this->getWorldWindow()->setCursorPos(centX, centY);
    }
  }

  /**
   * Move the mouse to the center of the window.
   */
  void Looker::centerCursor() const
  {
    int sizeX  = this->getWorldWindow()->getWidth();
    int sizeY  = this->getWorldWindow()->getHeight();
    int centX  = sizeX / 2; 
    int centY  = sizeY / 2;

    this->getWorldWindow()->setCursorPos(centX, centY);
  }

  /**
   * Toggle mouse look.
   * @param button The GLFW_MOUSE_BUTTON_n that was pressed.
   * @param action GLFW_PRESS or GLFW_RELEASE.
   * @param mods Modifier keys bit mask.
   */
  void Looker::onMouseButton(int button, int action, int mods)
  {
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
    {
      this->centerCursor();

      if (this->mouseLook)
        this->getWorldWindow()->showCursor();
      else
        this->getWorldWindow()->hideCursor();

      this->mouseLook = !this->mouseLook;
    }
  }
}

