#ifndef _BUSYBIN_MOVE_PRUNER_H_
#define _BUSYBIN_MOVE_PRUNER_H_

#include "../../Model/RubiksCube.h"
#include <string>
using std::string;
#include <vector>
using std::vector;

namespace busybin
{
  /**
   * Class that's used to figure it moves can be pruned.  Used by
   * CubeSearchers.
   */
  class MovePruner
  {
  public:
    // Return true if move should be pruned (e.g. not performed and pruned
    // from the search tree).
    bool prune(const string& move, const vector<string>& moves) const;
    bool prune(const string& move, const string& lastMove) const;
    bool prune(RubiksCube::MOVE move, RubiksCube::MOVE lastMove) const;
  };
}

#endif

