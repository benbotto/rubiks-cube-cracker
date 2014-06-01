#ifndef _BUSYBIN_Looker_H_
#define _BUSYBIN_Looker_H_

#include "Command.h"
#include "../../Model/World.h"
#include "../../View/WorldWindow.h"
#include <functional>
using std::bind;
using std::ref;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
#include <utility>
using std::pair;

namespace busybin
{
  /**
   * Handles moving around in the world.
   */
  class Looker : public Command
  {
    bool mouseLook;

  public:
    Looker(World* pWorld, WorldWindow* pWorldWnd);
    void onPulse(double elapsed);
    void centerCursor() const;
    void onMouseButton(int button, int action, int mods);
  };
}

#endif

