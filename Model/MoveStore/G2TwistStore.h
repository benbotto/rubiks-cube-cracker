#ifndef _BUSYBIN_G2_TWIST_STORE_H_
#define _BUSYBIN_G2_TWIST_STORE_H_

#include "MoveStore.h"
#include "../RubiksCube.h"

namespace busybin
{
  /**
   * Class for storing the available Rubik's Cube's twists in the G2 group.
   * <L2,R2,F2,B2,U,UPRIME,U2,D,DPRIME,D2>
   */
  class G2TwistStore : public MoveStore
  {
    const vector<RubiksCube::MOVE> moves;

  protected:
    const vector<RubiksCube::MOVE>& getMoves() const;

  public:
    G2TwistStore(RubiksCube& cube);
  };
}

#endif

