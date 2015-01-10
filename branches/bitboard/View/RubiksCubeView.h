#ifndef _BUSYBIN_RUBIKS_CUBE_VIEW_H_
#define _BUSYBIN_RUBIKS_CUBE_VIEW_H_

#include "../Model/RubiksCubeModel.h"
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
using std::right;

namespace busybin
{
  /**
   * Console view for the cube.
   */
  class RubiksCubeView
  {
  public:
    void render(const RubiksCubeModel& cube) const;
  };
}

#endif

