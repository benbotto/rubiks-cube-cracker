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

    return this->prune(move, lastMove);
  }

  /**
   * Check if the next move should be skipped.
   * @param move The next move, not yet applied.
   * @param lastMove The previous move.
   */
  bool CubeSearcher::prune(const string& move, const string& lastMove) const
  {
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
    if (move == "F'" && lastMove == "B'") return true;
    if (move == "L"  && lastMove == "R")  return true;
    if (move == "L2" && lastMove == "R2") return true;
    if (move == "L'" && lastMove == "R'") return true;
    if (move == "U"  && lastMove == "D")  return true;
    if (move == "U2" && lastMove == "D2") return true;
    if (move == "U'" && lastMove == "D'") return true;
    
    return false;
  }

  /**
   * Check if the next move should be skipped.
   * @param move The index of a twist move, not yet applied.
   * @param lastMove The last move index.
   */
  bool CubeSearcher::prune(RubiksCubeModel::MOVE move, RubiksCubeModel::MOVE lastMove) const
  {
    typedef RubiksCubeModel::MOVE M;

    if ((move == M::L || move == M::LPRIME || move == M::L2) &&
        (lastMove == M::L || lastMove == M::LPRIME || lastMove == M::L2))
      return true;

    if ((move == M::R || move == M::RPRIME || move == M::R2) &&
        (lastMove == M::R || lastMove == M::RPRIME || lastMove == M::R2))
      return true;

    if ((move == M::U || move == M::UPRIME || move == M::U2) &&
        (lastMove == M::U || lastMove == M::UPRIME || lastMove == M::U2))
      return true;

    if ((move == M::D || move == M::DPRIME || move == M::D2) &&
        (lastMove == M::D || lastMove == M::DPRIME || lastMove == M::D2))
      return true;

    if ((move == M::F || move == M::FPRIME || move == M::F2) &&
        (lastMove == M::F || lastMove == M::FPRIME || lastMove == M::F2))
      return true;

    if ((move == M::B || move == M::BPRIME || move == M::B2) &&
        (lastMove == M::B || lastMove == M::BPRIME || lastMove == M::B2))
      return true;

    if (move == M::F      && lastMove == M::B)      return true;
    if (move == M::F2     && lastMove == M::B2)     return true;
    if (move == M::FPRIME && lastMove == M::BPRIME) return true;
    if (move == M::L      && lastMove == M::R)      return true;
    if (move == M::L2     && lastMove == M::R2)     return true;
    if (move == M::LPRIME && lastMove == M::RPRIME) return true;
    if (move == M::U      && lastMove == M::D)      return true;
    if (move == M::U2     && lastMove == M::D2)     return true;
    if (move == M::UPRIME && lastMove == M::DPRIME) return true;

    return false;
  }
}

