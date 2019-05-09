#ifndef _BUSYBIN_GOALG3_PERMUTE_CORNERS_H_
#define _BUSYBIN_GOALG3_PERMUTE_CORNERS_H_

#include "../Goal.h"
#include "../../RubiksCube.h"
#include <string>
using std::string;
#include <set>
using std::set;
#include <array>
using std::array;
#include <cstdint>

namespace busybin
{
  /**
   * All 96 permutations of corners in G3 are stored by this class.  These
   * permutations are used by the G2->G3 goals.
   */
  class GoalG3_Permute_Corners : public Goal
  {
    typedef array<RubiksCube::COLOR, 16> perm_t;

    // Fast comparator for a permutation.
    struct PermComp
    {
      bool operator()(const perm_t& lhs, const perm_t& rhs) const;
    };

    set<perm_t, PermComp> perms;
    perm_t permToArr(const RubiksCube& cube) const;

  public:
    bool isSatisfied(RubiksCube& cube);
    bool permutationExists(const RubiksCube& cube) const;
    string getDescription() const;
  };
}

#endif

