#ifndef _BUSYBIN_RUBIKS_CUBE_EVALUATOR_H_
#define _BUSYBIN_RUBIKS_CUBE_EVALUATOR_H_

#include "../Model/RubiksCube.h"

namespace busybin
{
  class RubiksCubeEvaluator
  {
  public:
    RubiksCubeEvaluator();
    unsigned eval(const RubiksCube& cube) const;
  };
}

#endif

