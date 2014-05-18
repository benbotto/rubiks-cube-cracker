#ifndef _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_
#define _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_

#include "Scrambler.h"
#include "GASolver.h"
#include "../Model/RubiksCube.h"
#include "../Model/MoveStore.h"
#include "../Model/Chromosome.h"
#include "../View/RubiksCubeView.h"

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

