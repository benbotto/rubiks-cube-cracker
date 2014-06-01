#ifndef _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_
#define _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_

#include "Scrambler.h"
#include "CubeSearcher.h"
#include "../Model/RubiksCube.h"
#include "../Model/MoveStore.h"
#include "../Model/Goal/Goal.h"
#include "../Model/Goal/Goal1.h"
#include "../Model/Goal/Goal2.h"
#include "../View/RubiksCubeView.h"
#include <vector>
using std::vector;

namespace busybin
{
  /**
   * This class initializes and controls other classes.
   */
  class RubiksCubeController
  {
  public:
    RubiksCubeController();
    void start();
  };
}

#endif

