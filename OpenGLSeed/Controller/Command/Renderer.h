#ifndef _BUSYBIN_RENDERER_H_
#define _BUSYBIN_RENDERER_H_

#include "Command.h"
#include "../../Model/World.h"
#include "../../View/WorldWindow.h"
#include <functional>
using std::bind;
using std::ref;
using std::placeholders::_1;

namespace busybin
{
  /**
   * Calls draw on the world on every pulse.
   */
  class Renderer : public Command
  {
  public:
    Renderer(World* pWorld, WorldWindow* pWorldWnd);
    void onPulse(double elapsed);
  };
}

#endif

