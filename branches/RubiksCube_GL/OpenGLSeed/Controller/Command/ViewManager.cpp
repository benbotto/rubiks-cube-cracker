#include "ViewManager.h"

namespace busybin
{
  /**
   * Init.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, used to get the current width/heigth.
   */
  ViewManager::ViewManager(World* pWorld, WorldWindow* pWorldWnd) : Command(pWorld, pWorldWnd)
  {
    // Listen for frame buffer resize events.
    pWorldWnd->onFramebufferResize(bind(&ViewManager::onResize, ref(*this), _1, _2));

    // Setup the initial projection.
    this->onResize(pWorldWnd->getWidth(), pWorldWnd->getHeight());
  }

  /**
   * Fires when the WorldWindow is resized and sets up the projection matrix.
   * @param width The new width in pixels.
   * @param height The new height in pixels.
   */
  void ViewManager::onResize(int width, int height)
  {
    // Calculate the new projection matrix.  Field of view y is 60 degrees.
    this->getWorld()->getMatrixStack().topProjection() = perspective(pi<float>() / 3,
      static_cast<float>(width) / static_cast<float>(height),
      .01f, 1000.0f);
  }
}

