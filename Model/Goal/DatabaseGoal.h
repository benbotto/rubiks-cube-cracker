#ifndef _BUSYBIN_DATABASE_GOAL_H_
#define _BUSYBIN_DATABASE_GOAL_H_

#include "Goal.h"
#include "../PatternDatabase/PatternDatabase.h"
#include <cstdint>

namespace busybin
{
  class DatabaseGoal : public Goal
  {
    PatternDatabase* pDatabase;

  public:
    DatabaseGoal(PatternDatabase* pDatabase);
    bool isSatisfied(RubiksCube& cube);
    bool index(const RubiksCube& cube, uint8_t numMoves);
    bool index(const uint32_t ind,  uint8_t numMoves);
    uint8_t getNumMoves(const RubiksCube& cube) const;
    uint8_t getNumMoves(const uint32_t ind) const;
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
  };
}

#endif
