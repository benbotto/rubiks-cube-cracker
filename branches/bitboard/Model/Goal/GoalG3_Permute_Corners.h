#ifndef _BUSYBIN_GOALG3_PERMUTE_CORNERS_H_
#define _BUSYBIN_GOALG3_PERMUTE_CORNERS_H_

#include "Goal.h"
#include "../RubiksCubeModel.h"
#include <string>
using std::string;
#include <set>
using std::set;

namespace busybin
{
  /**
   * All permutations of corners in G3.
   */
  class GoalG3_Permute_Corners : public Goal
  {
    set<string> perms;
    string permToString(const RubiksCubeModel& cube) const;

  public:
    bool isSatisfied(RubiksCubeModel& cube);
    bool permutationExists(const RubiksCubeModel& cube) const;
    string getDescription() const;
  };
}

#endif

