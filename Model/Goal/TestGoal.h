#ifndef _BUSYBIN_TEST_GOAL_H_
#define _BUSYBIN_TEST_GOAL_H_

#include "Goal.h"
#include "DatabaseGoal.h"
#include "../RubiksCube.h"
#include "../RubiksCubeIndexModel.h"
#include "../PatternDatabase/TestPatternDatabase.h"
#include <cstdint>
#include <map>
using std::map;
#include <array>
using std::array;
#include <iostream>
using std::cout;
using std::endl;

namespace busybin
{
  /**
   * Test goal for checking solvers.
   */
  class TestGoal : public DatabaseGoal
  {
  public:
    TestGoal(TestPatternDatabase* pDatabase);
    string getDescription() const;
  };
}

#endif

