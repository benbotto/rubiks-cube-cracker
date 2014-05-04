#ifndef _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_
#define _BUSYBIN_RUBIKS_CUBE_CONTROLLER_H_

#include "../Model/RubiksCube.h"
#include "../View/RubiksCubeView.h"
#include "ChromosomeGenerator.h"
#include "RubiksCubeEvaluator.h"
#include <map>
using std::map;
#include <string>
using std::string;
#include <sstream>
using std::istringstream;
#include <functional>
using std::function;
using std::bind;
#include <algorithm>
using std::copy;
#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::getline;

namespace busybin
{
  class RubiksCubeController
  {
    typedef function<void()>        moveFunc_t;
    typedef map<string, moveFunc_t> moveMap_t;

    RubiksCube          cube;
    RubiksCubeView      view;
    RubiksCubeEvaluator evaluator;
    moveMap_t           moveMap;
    vector<string>      chromosomes;

    void manualScramble();
  public:
    RubiksCubeController();
    void start();
  };
}

#endif

