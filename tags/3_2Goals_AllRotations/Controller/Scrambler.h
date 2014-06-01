#ifndef _BUSYBIN_SCRAMBLER_H_
#define _BUSYBIN_SCRAMBLER_H_

#include "../Model/MoveStore.h"
#include "../Model/RubiksCube.h"
#include "../View/RubiksCubeView.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::getline;
#include <string>
using std::string;
#include <sstream>
using std::istringstream;
#include <vector>
using std::vector;

namespace busybin
{
  /**
   * Class for scrabling the Rubik's Cube.
   */
  class Scrambler
  {
    const RubiksCube*     const cube;
    MoveStore*            const moveStore;
    const RubiksCubeView* const view;

  public:
    Scrambler(const RubiksCube& rCube, MoveStore& mStore,
      const RubiksCubeView& cubeView);
    void manualScramble();
  };
}

#endif

