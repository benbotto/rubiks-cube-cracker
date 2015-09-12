#ifndef _BUSYBIN_CUBE_DUMPER_H_
#define _BUSYBIN_CUBE_DUMPER_H_

#include "../../OpenGLSeed/Controller/Command/Command.h"
#include "../../Model/WorldObject/RubiksCube.h"
#include "../../View/RubiksCubeView.h"

namespace busybin
{
  /**
   * Prints the Cube Model to the console.
   */
  class CubeDumper : public Command
  {
    RubiksCube*    pCube;
    RubiksCubeView view;

  public:
    CubeDumper(World* pWorld, WorldWindow* pWorldWnd);
      void onKeypress(int key, int scancode, int action, int mods);
  };
}

#endif

