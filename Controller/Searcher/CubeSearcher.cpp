#include "CubeSearcher.h"

namespace busybin
{
  /**
   * Helper method to convert move indexes to moves.
   */
  vector<RubiksCube::MOVE> CubeSearcher::convertMoves(
    vector<uint8_t>& moveInds, MoveStore& moveStore) const
  {
    vector<RubiksCube::MOVE> moves;

    for (uint8_t moveInd : moveInds)
      moves.push_back(moveStore.getMove(moveInd));

    return moves;
  }
}

