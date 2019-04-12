#include "CubeSearcher.h"

namespace busybin
{
  /**
   * Check if the next move should be skipped.
   * @param move The next move, not yet applied.
   * @param moves A vector of moves leading up to move.
   */
  bool CubeSearcher::prune(const string& move, const vector<string>& moves) const
  {
    if (moves.size() == 0)
      return false;

    string lastMove = moves.back();

    // If the last move is the same as this move, no reason to attempt it.
    // e.g. L L is the same as L2.  L2 L2 is a 360 degree twist.
    // Two moves that can be accomplished in one.  For instance, L2 L is the
    // same as L'.  L2 L' is the same as L.  Commutative.
    // In other words, if two moves on the same side occur successively (the
    // start with the same letter), prune.
    if (move.at(0) == lastMove.at(0)) return true;

    // Commutative moves.  For example, F B is the same as B F.
    if (move == "F"  && lastMove == "B")  return true;
    if (move == "F2" && lastMove == "B2") return true;
    if (move == "L"  && lastMove == "R")  return true;
    if (move == "L2" && lastMove == "R2") return true;
    if (move == "U"  && lastMove == "D")  return true;
    if (move == "U2" && lastMove == "D2") return true;
    
    return false;
  }
}

