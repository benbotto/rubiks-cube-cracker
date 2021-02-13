#ifndef _BUSYBIN_CUBE_SCRAMBLER_H_
#define _BUSYBIN_CUBE_SCRAMBLER_H_

#include "CubeMover.h"
#include "../../OpenGLSeed/Controller/Command/Command.h"
#include "../../Model/RubiksCube.h"
#include "../../Model/RubiksCubeModel.h"
#include "../../Model/WorldObject/RubiksCubeWorldObject.h"
#include "../../Model/MoveStore/TwistStore.h"
#include "../Searcher/MovePruner.h"
#include "../../Util/Random.h"
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
using std::setfill;
using std::left;

namespace busybin
{
  /**
   * A command that scrambles the cube on keypress.
   */
  class CubeScrambler : public Command
  {
    RubiksCubeWorldObject* pCube;
    CubeMover*             pMover;

  public:
    CubeScrambler(World* pWorld, WorldWindow* pWorldWnd, CubeMover* pMover);
    void onKeypress(int key, int scancode, int action, int mods);
  };
}

#endif
