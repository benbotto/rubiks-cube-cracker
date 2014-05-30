#ifndef _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_
#define _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_

#include "Command/CubeMover.h"
#include "../OpenGLSeed/View/WorldWindow.h"
#include "../OpenGLSeed/Controller/Command/ViewManager.h"
#include "../OpenGLSeed/Controller/Command/Renderer.h"
#include "../OpenGLSeed/Controller/Command/Mover.h"
#include "../OpenGLSeed/Controller/Command/Looker.h"
#include "../Model/RubiksCubeWorld.h"
#include <iostream>
using std::cout;
using std::endl;
#include <exception>
using std::exception;

namespace busybin
{
  class RubiksCubeController
  {
  public:
    void run();
  };
}

#endif

