#ifndef _BUSYBIN_CUBE_SEARCHER_H_
#define _BUSYBIN_CUBE_SEARCHER_H_

#include "../Model/RubiksCubeModel.h"
#include "../Model/Goal/Goal.h"
#include "../Model/MoveStore/MoveStore.h"
#include <vector>
using std::vector;
#include <string>
using std::string;

namespace busybin
{
  /**
   * Base class for CubeSearchers.  A CubeSearcher is a class that searchers
   * for a Goal using a MoveStore (a set of moves).
   */
  class CubeSearcher
  {
  public:
    // Find goal using moveStore and return the list of moves required to
    // achieve goal.
    virtual vector<string> findGoal(
      Goal& goal,
      RubiksCubeModel& cube,
      MoveStore& moveStore) = 0;

    // Return true if move should be pruned (e.g. not performed and pruned
    // from the search tree).
    virtual bool prune(const string& move, const vector<string>& moves) const;
  };
}

#endif

