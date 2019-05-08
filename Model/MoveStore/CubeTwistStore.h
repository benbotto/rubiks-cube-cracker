#ifndef _BUSYBIN_CUBE_TWIST_STORE_H_
#define _BUSYBIN_CUBE_TWIST_STORE_H_

#include "TwistStore.h"
#include "../WorldObject/RubiksCubeWorldObject.h"

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
    CubeTwistStore(RubiksCubeWorldObject& cube);
    const MoveStore::moveFuncMap_t& getMoveMap() const;
  };
}

#endif

