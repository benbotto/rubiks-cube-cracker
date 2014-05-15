#ifndef _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_
#define _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_

#include "Scrambler.h"
#include "RubiksCubeEvaluator.h"
#include "../Model/RubiksCube.h"
#include "../Model/MoveStore.h"
#include "../Model/Chromosome.h"
#include "../View/RubiksCubeView.h"
#include "../Util/Random.h"
#include <map>
using std::map;
#include <string>
using std::string;
#include <vector>
using std::vector;

namespace busybin
{
  class RubiksCubeController
  {
    typedef vector<vector<Chromosome> > population_t;

    RubiksCube            cube;
    RubiksCubeView        cubeView;
    RubiksCubeEvaluator   evaluator;
    MoveStore             moveStore;
    Scrambler             scrambler;
    Random                rand;
    population_t          populations;

  public:
    RubiksCubeController();
    void start();
  };
}

#endif

