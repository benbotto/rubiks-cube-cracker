#ifndef _BUSYBIN_IDA_CUBE_SEARCHER_H_
#define _BUSYBIN_IDA_CUBE_SEARCHER_H_

#include "CubeSearcher.h"
#include "../../Model/RubiksCubeModel.h"
#include "../../Model/Goal/Goal.h"
#include "../../Model/MoveStore/MoveStore.h"
#include "../../Util/AutoTimer.h"
#include "../../Model/PatternDatabase/PatternDatabase.h"
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <queue>
using std::priority_queue;
#include <functional>
using std::greater;
#include <cstdint>

namespace busybin
{
  /**
   * Iterative deepening A* searcher for the cube.
   */
  class IDACubeSearcher : public CubeSearcher
  {
    struct PrioritizedMove
    {
      uint8_t moveInd;
      uint8_t estMoves; // Priority.
      bool operator>(const PrioritizedMove& rhs) const
      {
        return this->estMoves > rhs.estMoves;
      }
    };

    const PatternDatabase* pPatternDB;

    uint8_t findGoal(Goal& goal, RubiksCubeModel& cube, MoveStore& moveStore,
      uint8_t bound, vector<string>& moves, bool& solved);

  public:
    IDACubeSearcher(const PatternDatabase* pPatternDB);
    vector<string> findGoal(Goal& goal, RubiksCubeModel& cube, MoveStore& moveStore);
  };
}

#endif
