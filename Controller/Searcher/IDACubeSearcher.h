#ifndef _BUSYBIN_IDA_CUBE_SEARCHER_H_
#define _BUSYBIN_IDA_CUBE_SEARCHER_H_

#include "CubeSearcher.h"
#include "../../Model/RubiksCubeIndexModel.h"
#include "../../Model/Goal/Goal.h"
#include "../../Model/MoveStore/MoveStore.h"
#include "../../Util/AutoTimer.h"
#include "../../Util/RubiksCubeException.h"
#include "../../Model/PatternDatabase/PatternDatabase.h"
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <array>
using std::array;
#include <queue>
using std::priority_queue;
#include <stack>
using std::stack;
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
      RubiksCubeIndexModel cube;
      RubiksCube::MOVE move;
      uint8_t estMoves; // Priority.  Least number of moves to most.
      bool operator>(const PrioritizedMove& rhs) const
      {
        return this->estMoves > rhs.estMoves;
      }
    };

    struct Node
    {
      RubiksCubeIndexModel cube;
      RubiksCube::MOVE move;
      uint8_t depth;
    };

    const PatternDatabase* pPatternDB;

  public:
    IDACubeSearcher(const PatternDatabase* pPatternDB);
    vector<RubiksCube::MOVE> findGoal(Goal& goal, RubiksCube& cube,
      MoveStore& moveStore);
  };
}

#endif

