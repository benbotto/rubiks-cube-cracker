#ifndef _BUSYBIN_RUBIKS_CUBE_CHROMOSOME_GENERATOR_H_
#define _BUSYBIN_RUBIKS_CUBE_CHROMOSOME_GENERATOR_H_

#include "../Model/RubiksCube.h"
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <array>
using std::array;
#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;
#include <chrono>
using std::chrono::system_clock;

namespace busybin
{
  class ChromosomeGenerator
  {
    array<string, 18> moves;
    default_random_engine generator;
    uniform_int_distribution<int> moveDist;

  public:
    ChromosomeGenerator();
    vector<string> generateChromosome(unsigned size);
  };
}

#endif

