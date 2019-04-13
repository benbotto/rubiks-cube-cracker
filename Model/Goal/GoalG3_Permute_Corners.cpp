#include "GoalG3_Permute_Corners.h"

namespace busybin
{
  /**
   * Convert a permutation of the corners to a string.
   * @param cube The cube.
   */
  GoalG3_Permute_Corners::perm_t GoalG3_Permute_Corners::permToArr(const RubiksCubeModel& cube) const
  {
    // Note that two facets of a corner dictate the orientation of a corner.
    // The third facet doesn't need to be stored, therefore.  For example,
    // there are two corner cubies with red and blue facets: RBW, and RBY.
    // With red up top and blue on the left, the RBW cubie occupies the top,
    // left, front position.  There's no possible way to get the RBY cubie to
    // occupy that same position such that red is on top and blue is on the
    // left.  Indexing top, left, front, the RBY corner cubie can be in three
    // permutations: RYB, YBR, BRY, but never RBY.
    perm_t perm =
    {{
      cube.get(FACE::UP,    0, 0),
      cube.get(FACE::LEFT,  0, 0),

      cube.get(FACE::UP,    2, 0),
      cube.get(FACE::LEFT,  0, 2),

      cube.get(FACE::UP,    0, 2),
      cube.get(FACE::RIGHT, 0, 2),

      cube.get(FACE::UP,    2, 2),
      cube.get(FACE::RIGHT, 0, 0),

      cube.get(FACE::DOWN,  2, 0),
      cube.get(FACE::LEFT,  2, 0),

      cube.get(FACE::DOWN,  0, 0),
      cube.get(FACE::LEFT,  2, 2),

      cube.get(FACE::DOWN,  2, 2),
      cube.get(FACE::RIGHT, 2, 2),

      cube.get(FACE::DOWN,  0, 2),
      cube.get(FACE::RIGHT, 2, 0),
    }};

    return perm;
  }

  /**
   * If the corner permutation is unique, save it in a set.  There are a
   * total of 96 possible corner permutations that can be achieved from the
   * solved state using only 180-degree turns.
   * @param cube The cube.
   */
  bool GoalG3_Permute_Corners::isSatisfied(RubiksCubeModel& cube)
  {
    perm_t perm = this->permToArr(cube);

    if (this->perms.count(perm) == 0)
    {
      this->perms.insert(perm);

      // There are 96 total permutations.
      if (this->perms.size() == 96)
        return true;
    }

    return false;
  }

  /**
   * Check if the permutation of the cube's corners is one that can be achieved by only
   * 180-degree twists.
   * @cube The cube.
   */
  bool GoalG3_Permute_Corners::permutationExists(const RubiksCubeModel& cube) const
  {
    perm_t perm = this->permToArr(cube);
    return this->perms.count(perm) == 1;
  }

  /**
   * Describe the goal.
   */
  string GoalG3_Permute_Corners::getDescription() const
  {
    return "All permutations of corners in G3.";
  }

  /**
   * Quick compare for two permutation arrays.
   * @param lhs The left array.
   * @param rhs The right array.
   */
  bool GoalG3_Permute_Corners::PermComp::operator()(const perm_t& lhs, const perm_t& rhs) const
  {
    // 16 corner facets are stored (see note in the ctor).  Each facet is an
    // 8-bit char (a COLOR), so the array of corners can be treated as two
    // 64-bit ints.  This is quite a bit faster than the default
    // set comparator.
    int64_t lDiff = *(int64_t*)&lhs[0] - *(int64_t*)&rhs[0];

    if (lDiff < 0)
      return true;
    else if (lDiff == 0)
    {
      if (*(int64_t*)&lhs[8] < *(int64_t*)&rhs[8])
        return true;
    }

    return false;
  }
}

