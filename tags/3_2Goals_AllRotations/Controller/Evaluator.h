#ifndef _BUSYBIN_EVALUATOR_H_
#define _BUSYBIN_EVALUATOR_H_

#include "../Model/RubiksCube.h"

namespace busybin
{
  class Evaluator
  {
  public:
    Evaluator();
    unsigned eval(const RubiksCube& cube) const;
  };
}

#endif

