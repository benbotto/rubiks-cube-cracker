#ifndef _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_
#define _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_

#include "Command/CubeMover.h"
#include "Command/ThistlethwaiteCubeSolver.h"
#include "Command/CubeDumper.h"
#include "../OpenGLSeed/View/WorldWindow.h"
#include "../OpenGLSeed/Controller/Command/ViewManager.h"
#include "../OpenGLSeed/Controller/Command/Renderer.h"
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

