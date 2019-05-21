#ifndef _BUSYBIN_TWIST_STORE_H_
#define _BUSYBIN_TWIST_STORE_H_

#include "MoveStore.h"
#include "../RubiksCube.h"

namespace busybin
{
  /**
   * Base class for the TwistStore classes.
   */
  class TwistStore : public MoveStore
  {
    const vector<RubiksCube::MOVE> moves;

  protected:
    const vector<RubiksCube::MOVE>& getMoves() const;

  public:
    TwistStore(RubiksCube& cube);

    void move(uint8_t ind);
    void invert(uint8_t ind);
  };
}

#endif

