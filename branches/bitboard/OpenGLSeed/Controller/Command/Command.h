#ifndef _BUSYBIN_COMMAND_H_
#define _BUSYBIN_COMMAND_H_

#include "../../Model/World.h"
#include "../../View/WorldWindow.h"

namespace busybin
{
  /**
   * Base class for commands.
   */
  class Command
  {
    World*       pWorld;
    WorldWindow* pWorldWnd;
  public:
    Command(World* pWorld, WorldWindow* pWorldWnd);

    World* getWorld() const;
    void setWorld(World* pWorld);

    WorldWindow* getWorldWindow() const;
    void setWorldWindow(WorldWindow* pWorldWindow);
  };
}

#endif

