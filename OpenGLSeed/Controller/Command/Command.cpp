#include "Command.h"

namespace busybin
{
  /**
   * Base command class.
   * @param pWorld A pointer to the world that must remain in scope.
   * @param pWorldWnd A pointer to the world window that must remain in scope.
   */
  Command::Command(World* pWorld, WorldWindow* pWorldWnd)
  {
    this->setWorld(pWorld);
    this->setWorldWindow(pWorldWnd);
  }

  /**
   * Set the world pointer.
   */
  World* Command::getWorld() const
  {
    return this->pWorld;
  }

  /**
   * Set the world pointer.
   * @param pWorld A pointer to the world that must remain in scope.
   */
  void Command::setWorld(World* pWorld)
  {
    this->pWorld = pWorld;
  }

  /**
   * Set the WorldWindow pointer.
   */
  WorldWindow* Command::getWorldWindow() const
  {
    return this->pWorldWnd;
  }

  /**
   * Set the WorldWindow pointer.
   * @param pWorldWindow A pointer to the WorldWindow that must remain in scope.
   */
  void Command::setWorldWindow(WorldWindow* pWorldWnd)
  {
    this->pWorldWnd = pWorldWnd;
  }
}

