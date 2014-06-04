#ifndef _BUSYBIN_GOAL_H_
#define _BUSYBIN_GOAL_H_

#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Base class for cube solution goals.
   */
  class Goal
  {
  protected:
    bool LUF;
    bool LUB;
    bool LDF;
    bool LDB;
    bool RUF;
    bool RUB;
    bool RDF;
    bool RDB;
    bool LU;
    bool LF;
    bool LB;
    bool LD;
    bool DF;
    bool DB;
    bool UF;
    bool UB;
    bool RU;
    bool RF;
    bool RB;
    bool RD;

    void updateSolved(const RubiksCubeModel& cube);

  public:
    virtual bool isSatisfied(RubiksCubeModel& cube) = 0;
  };
}

#endif

