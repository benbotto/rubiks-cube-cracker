#ifndef _BUSYBIN_G3_TWIST_STORE_H_
#define _BUSYBIN_G3_TWIST_STORE_H_

#include "TwistStore.h"
#include "../RubiksCube.h"
#include <array>
using std::array;

namespace busybin
{
  /**
   * Class for storing the available Rubik's Cube's twists in the G3 group.
   * <L2,R2,F2,B2,U2,D2>
   */
  class G3TwistStore : public MoveStore
  {
    const vector<RubiksCube::MOVE> moves;

  protected:
    const vector<RubiksCube::MOVE>& getMoves() const;

  public:
    G3TwistStore(RubiksCube& cube);
  };
}

#endif

