#include "MovePruner.h"

namespace busybin
{
  /**
   * Check if the next move should be skipped.
   * @param move The next move, not yet applied.
   * @param moves A vector of moves leading up to move.
   */
  bool MovePruner::prune(const string& move, const vector<string>& moves) const
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
  bool MovePruner::prune(const string& move, const string& lastMove) const
  {
    // If the last move is the same as this move, no reason to attempt it.
    // e.g. L L is the same as L2.  L2 L2 is a 360 degree twist.
    // Two moves that can be accomplished in one.  For instance, L2 L is the
    // same as L'.  L2 L' is the same as L.  Commutative.
    // In other words, if two moves on the same side occur successively (the
    // start with the same letter), prune.
    if (move.at(0) == lastMove.at(0)) return true;

    // Commutative moves.  For example, F B is the same as B F.
    if (move.at(0) == 'F' && lastMove.at(0) == 'B') return true;
    if (move.at(0) == 'L' && lastMove.at(0) == 'R') return true;
    if (move.at(0) == 'U' && lastMove.at(0) == 'D') return true;

    return false;
  }

  /**
   * Check if the next move should be skipped.
   * @param move The index of a twist move, not yet applied.
   * @param lastMove The last move index.
   */
  bool MovePruner::prune(RubiksCube::MOVE move, RubiksCube::MOVE lastMove) const
  {
    typedef RubiksCube::MOVE M;

    // Two twists of the same face.
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

    // Commutative moves.
    if ((move == M::F || move == M::FPRIME || move == M::F2) &&
        (lastMove == M::B || lastMove == M::BPRIME || lastMove == M::B2))
      return true;

    if ((move == M::L || move == M::LPRIME || move == M::L2) &&
        (lastMove == M::R || lastMove == M::RPRIME || lastMove == M::R2))
      return true;

    if ((move == M::U || move == M::UPRIME || move == M::U2) &&
        (lastMove == M::D || lastMove == M::DPRIME || lastMove == M::D2))
      return true;

    return false;
  }
}

