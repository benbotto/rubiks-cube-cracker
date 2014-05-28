#include "Renderer.h"

namespace busybin
{
  /**
   * Init.
   * @param pWorld Pointer to the world (must remain in scope).
   * @param pWorldWnd The world window, used to get the current width/heigth.
   */
  Renderer::Renderer(World* pWorld, WorldWindow* pWorldWnd) : Command(pWorld, pWorldWnd)
  {
    // Listen for pulse events.
    pWorldWnd->onPulse(bind(&Renderer::onPulse, ref(*this), _1));
  }

  /**
   * Fires when the WorldWindow pulses and renders the world.
   * @param elapsed The number of elapsed seconds since the last pulse.
   */
  void Renderer::onPulse(double elapsed)
  {
    this->getWorld()->draw(elapsed);
  }
}

