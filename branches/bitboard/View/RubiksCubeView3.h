#ifndef _BUSYBIN_RUBIKS_CUBE_VIEW3_H_ // TODO
#define _BUSYBIN_RUBIKS_CUBE_VIEW3_H_ // TODO

#include "../Model/RubiksCubeModel3.h" // TODO
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
using std::setfill;
using std::left;
using std::right;
using std::hex;
using std::dec;
#include <bitset>
using std::bitset;

namespace busybin
{
  /**
   * Console view for the cube.
   */
  class RubiksCubeView3 // TODO
  {
  public:
    void render(const RubiksCubeModel3& cube) const; // TODO
  };
}

#endif

