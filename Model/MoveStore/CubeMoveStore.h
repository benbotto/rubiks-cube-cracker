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
    MoveStore::rotMap_t  rotMap;

  protected:
    MoveStore::moveMap_t& getMoveMap();
    MoveStore::rotMap_t& getRotationMap();

  public:
    CubeMoveStore(RubiksCube& cube);
    const MoveStore::moveMap_t& getMoveMap() const;
    const MoveStore::rotMap_t& getRotationMap() const;
  };
}

#endif

