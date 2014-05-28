#ifndef _BUSYBIN_VIEW_MANAGER_H_
#define _BUSYBIN_VIEW_MANAGER_H_

#include "Command.h"
#include "../../Model/World.h"
#include "../../View/WorldWindow.h"
#include <functional>
using std::bind;
using std::ref;
using std::placeholders::_1;
using std::placeholders::_2;
#include <glm/gtc/constants.hpp>
using glm::pi;
#include <glm/gtc/matrix_transform.hpp>
using glm::perspective;

namespace busybin
{
  /**
   * Handles resize events on the WorldWindow.
   */
  class ViewManager : public Command
  {
  public:
    ViewManager(World* pWorld, WorldWindow* pWorldWnd);
    void onResize(int width, int height);
  };
}

#endif

