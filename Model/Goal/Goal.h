#ifndef _BUSYBIN_GOAL_H_
#define _BUSYBIN_GOAL_H_

#include "../RubiksCube.h"
#include <string>
using std::string;

namespace busybin
{
  /**
   * Base class for cube solution goals.
   */
  class Goal
  {
  protected:
    typedef RubiksCube::FACE  FACE;
    typedef RubiksCube::COLOR COLOR;

  public:
    virtual bool isSatisfied(RubiksCube& cube) = 0;
    virtual string getDescription() const = 0;
    virtual bool index(const RubiksCube& cube, size_t numMoves);
  };
}

#endif

