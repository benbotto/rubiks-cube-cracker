#ifndef _BUSYBIN_CUBE_MOVER_H_
#define _BUSYBIN_CUBE_MOVER_H_

#include "../../Model/WorldObject/RubiksCube.h"
#include "../../OpenGLSeed/Controller/Command/Command.h"
#include "../../OpenGLSeed/Model/World.h"
#include "../../OpenGLSeed/View/WorldWindow.h"
#include <functional>
using std::bind;
using std::ref;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;

namespace busybin
{
  /**
   * Handles moving the cube around.
   */
  class CubeMover : public Command
  {
    RubiksCube* pCube;

  public:
    CubeMover(World* pWorld, WorldWindow* pWorldWnd);
    void onKeypress(int key, int scancode, int action, int mods);
  };
}

#endif

