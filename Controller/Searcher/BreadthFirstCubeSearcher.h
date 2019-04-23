#ifndef _BUSYBIN_BREADTH_FIRST_CUBE_SEARCHER_H_
#define _BUSYBIN_BREADTH_FIRST_CUBE_SEARCHER_H_

#include "CubeSearcher.h"
#include "../../Model/RubiksCubeModel.h"
#include "../../Model/Goal/Goal.h"
#include "../../Model/MoveStore/MoveStore.h"
#include "../../Util/AutoTimer.h"
#include "../../View/RubiksCubeView.h"
#include <vector>
using std::vector;
#include <queue>
using std::queue;
#include <stack>
using std::stack;
#include <string>
using std::string;
#include <algorithm>
using std::reverse;
#include <memory>
using std::shared_ptr;
#include <cstdint>

namespace busybin
{
  /**
   * A breadth first search implementation for the Rubik's Cube.
   */
  class BreadthFirstCubeSearcher : public CubeSearcher
  {
    struct Node;

    typedef shared_ptr<Node> nodePtr_t;

    struct Node
    {
      uint8_t   moveInd;
      nodePtr_t pParent;
      uint8_t   depth;
    };

    void moveToNode(const Node* pNode, MoveStore& moveStore, vector<string>& moves) const;
    void revertMoves(const Node* pNode, MoveStore& moveStore) const;

  public:
    vector<string> findGoal(Goal& goal, RubiksCubeModel& cube,
      MoveStore& moveStore);
  };
}

#endif

