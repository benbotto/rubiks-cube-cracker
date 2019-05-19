#ifndef _BUSYBIN_EDGE_PERMUTATION_DATABASE_GOAL_H_
#define _BUSYBIN_EDGE_PERMUTATION_DATABASE_GOAL_H_

#include "../DatabaseGoal.h"
#include "../../PatternDatabase/Korf/EdgePermutationPatternDatabase.h"
#include <cstddef>
using std::size_t;

namespace busybin
{
  /**
   * Goal for populating the EdgePermutationPatternDatabase, which is the
   * permutations of the 12 edges.
   */
  class EdgePermutationDatabaseGoal : public DatabaseGoal
  {
  public:
    EdgePermutationDatabaseGoal(EdgePermutationPatternDatabase* pDatabase);
    string getDescription() const;
  };
}

#endif
