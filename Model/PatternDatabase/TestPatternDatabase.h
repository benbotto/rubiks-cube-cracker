#ifndef _BUSYBIN_CORNER_ORIENTATION_PATTERN_DATABASE_H_
#define _BUSYBIN_CORNER_ORIENTATION_PATTERN_DATABASE_H_

#include "PatternDatabase.h"
#include "PermutationIndexer.h"
#include "../RubiksCube.h"
#include "../RubiksCubeIndexModel.h"
#include <cstdint>
#include <array>
using std::array;
#include <iostream>
using std::cout;
using std::endl;

namespace busybin
{
  /**
   * Database used for testing.
   */
  class TestPatternDatabase : public PatternDatabase
  {
    PermutationIndexer<8> permIndexer;

  public:
    TestPatternDatabase();
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif

