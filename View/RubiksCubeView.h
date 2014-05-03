#ifndef _BUSYBIN_RUBIKS_CUBE_VIEW_H_
#define _BUSYBIN_RUBIKS_CUBE_VIEW_H_

#include "../Model/RubiksCube.h"
#include <iostream>
using std::cout;
using std::endl;
using std::flush;
#include <iomanip>
using std::setw;
using std::right;

namespace busybin
{
  class RubiksCubeView
  {
  public:
    RubiksCubeView();
    void render(const RubiksCube& cube) const;
  };
}

#endif

