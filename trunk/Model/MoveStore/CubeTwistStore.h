#ifndef _BUSYBIN_CUBE_TWIST_STORE_H_
#define _BUSYBIN_CUBE_TWIST_STORE_H_

#include "TwistStore.h"
#include "../WorldObject/RubiksCube.h"

namespace busybin
{
  /**
   * Class for storing the available Rubik's Cube's twists.
   */
  class CubeTwistStore : public TwistStore
  {
    MoveStore::moveFuncMap_t moveMap;

  protected:
    MoveStore::moveFuncMap_t& getMoveMap();

  public:
    CubeTwistStore(RubiksCube& cube);
    const MoveStore::moveFuncMap_t& getMoveMap() const;
  };
}

#endif

