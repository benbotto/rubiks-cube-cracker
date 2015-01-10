#ifndef _BUSYBIN_RUBIKS_CUBE_VIEW2_H_ // TODO
#define _BUSYBIN_RUBIKS_CUBE_VIEW2_H_ // TODO

#include "../Model/RubiksCubeModel2.h" // TODO
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
  class RubiksCubeView2 // TODO
  {
  public:
    void renderRaw(const RubiksCubeModel2& cube) const; // TODO
    void printFaceRaw(unsigned face) const;

    void render(const RubiksCubeModel2& cube) const; // TODO
  };
}

#endif

