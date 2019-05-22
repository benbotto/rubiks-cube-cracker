#ifndef _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_
#define _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_

#include "Command/CubeMover.h"
#include "Command/Solver/ThistlethwaiteCubeSolver.h"
#include "Command/Solver/KorfCubeSolver.h"
#include "Command/CubeDumper.h"
#include "Command/CubeScrambler.h"
#include "../OpenGLSeed/View/WorldWindow.h"
#include "../OpenGLSeed/Controller/Command/ViewManager.h"
#include "../OpenGLSeed/Controller/Command/Renderer.h"
#include "../Model/RubiksCubeWorld.h"
#include "../Util/ThreadPool.h"
#include <iostream>
using std::cout;
using std::endl;
#include <exception>
using std::exception;
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

namespace busybin
{
  class RubiksCubeController
  {
  public:
    void run();
  };
}

#endif

