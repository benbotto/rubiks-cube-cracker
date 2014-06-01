#ifndef _BUSYBIN_CUBE_MOVE_STORE_H_
#define _BUSYBIN_CUBE_MOVE_STORE_H_

#include "MoveStore.h"
#include "../WorldObject/RubiksCube.h"

namespace busybin
{
  /**
   * Class for storing the available Rubik's Cube's moves.
   */
  class CubeMoveStore : public MoveStore
  {
    MoveStore::moveMap_t moveMap;

  protected:
    MoveStore::moveMap_t& getMoveMap();

  public:
    CubeMoveStore(RubiksCube& cube);
    const MoveStore::moveMap_t& getMoveMap() const;
  };
}

#endif

