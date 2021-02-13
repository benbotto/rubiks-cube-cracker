#ifndef _BUSYBIN_G1_TWIST_STORE_H_
#define _BUSYBIN_G1_TWIST_STORE_H_

#include "MoveStore.h"
#include "../RubiksCube.h"

namespace busybin
{
  /**
   * Class for storing the available Rubik's Cube's twists in the G1 group.
   * This group excludes quarter turns of F and B.
   */
  class G1TwistStore : public MoveStore
  {
    const vector<RubiksCube::MOVE> moves;

  protected:
    const vector<RubiksCube::MOVE>& getMoves() const;

  public:
    G1TwistStore(RubiksCube& cube);
  };
}

#endif

