#include "Goal2.h"

namespace busybin
{
  /**
   * Init.
   */
  Goal2::Goal2()
  {
  }

  /**
   * Check if an adjacent edge is solved.
   * @param cube The cube.
   */
  bool Goal2::isSatisfied(const RubiksCubeModel& cube)
  {
    typedef RubiksCubeModel::FACE F;

    bool ul = cube.isSolved(F::UP, F::LEFT);
    bool uf = cube.isSolved(F::UP, F::FRONT);
    bool ur = cube.isSolved(F::UP, F::RIGHT);
    bool ub = cube.isSolved(F::UP, F::BACK);

    bool fl = cube.isSolved(F::FRONT, F::LEFT);
    bool fr = cube.isSolved(F::FRONT, F::RIGHT);

    bool bl = cube.isSolved(F::BACK, F::LEFT);
    bool br = cube.isSolved(F::BACK, F::RIGHT);

    bool dl = cube.isSolved(F::DOWN, F::LEFT);
    bool df = cube.isSolved(F::DOWN, F::FRONT);
    bool dr = cube.isSolved(F::DOWN, F::RIGHT);
    bool db = cube.isSolved(F::DOWN, F::BACK);

    return
      (ul && uf) ||
      (ul && ub) ||
      (ul && fl) ||
      (ul && bl) ||

      (ur && uf) ||
      (ur && ub) ||
      (ur && fr) ||
      (ur && br) ||

      (dl && df) ||
      (dl && db) ||
      (dl && fl) ||
      (dl && bl) ||

      (dr && df) ||
      (dr && db) ||
      (dr && fr) ||
      (dr && br);
  }
}
