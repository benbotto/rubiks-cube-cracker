#ifndef _BUSYBIN_ROTATION_STORE_H_
#define _BUSYBIN_ROTATION_STORE_H_

#include "MoveStore.h"
#include "../RubiksCube.h"

namespace busybin
{
  /**
   * Base class for the RotationStore classes.
   */
  class RotationStore : public MoveStore
  {
    const vector<RubiksCube::MOVE> moves;

  protected:
    const vector<RubiksCube::MOVE>& getMoves() const;

  public:
    RotationStore(RubiksCube& cube);
  };
}

#endif

