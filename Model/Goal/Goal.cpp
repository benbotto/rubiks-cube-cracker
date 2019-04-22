#include "Goal.h"

namespace busybin
{
  /**
   * Sub-classes can override this to put a cube state into a PatternDatabase.  This
   * is a default do-nothing implementations.  Sub-classes should return true
   * if the cube is indexed, false if not (e.g. it's already indexed).
   * @param cube The cube model to index.
   * @param numMoves The number of moves to get from this cube state back to
   * the solved state.
   */
  bool Goal::index(const RubiksCubeModel& cube, size_t numMoves)
  {
    return false;
  }
}

