#ifndef _BUSYBIN_CUBE_SEARCHER_H_
#define _BUSYBIN_CUBE_SEARCHER_H_

#include "./MovePruner.h"
#include "../../Model/RubiksCubeModel.h"
#include "../../Model/Goal/Goal.h"
#include "../../Model/MoveStore/MoveStore.h"
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
  protected:
    MovePruner pruner;

  public:
    // Find goal using moveStore and return the list of moves required to
    // achieve goal.
    virtual vector<string> findGoal(
      Goal& goal,
      RubiksCubeModel& cube,
      MoveStore& moveStore) = 0;
  };
}

#endif

