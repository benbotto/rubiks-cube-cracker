#ifndef _BUSYBIN_MOVER_H_
#define _BUSYBIN_MOVER_H_

#include "Command.h"
#include "../../Model/World.h"
#include "../../View/WorldWindow.h"
#include <functional>
using std::bind;
using std::ref;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;
#include <map>
using std::map;

namespace busybin
{
  /**
   * Handles moving around in the world.
   */
  class Mover : public Command
  {
    map<char, bool> keys;
  public:
    Mover(World* pWorld, WorldWindow* pWorldWnd);
    void onKeypress(int key, int scancode, int action, int mods);
    void onPulse(double elapsed);
  };
}

#endif

