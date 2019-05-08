#ifndef _BUSYBIN_CUBE_ROTATION_STORE_H_
#define _BUSYBIN_CUBE_ROTATION_STORE_H_

#include "RotationStore.h"
#include "../WorldObject/RubiksCubeWorldObject.h"

namespace busybin
{
  /**
   * Class for storing the available Rubik's Cube's rotations.
   */
  class CubeRotationStore : public RotationStore
  {
    MoveStore::moveFuncMap_t moveMap;

  protected:
    MoveStore::moveFuncMap_t& getMoveMap();

  public:
    CubeRotationStore(RubiksCubeWorldObject& cube);
    const MoveStore::moveFuncMap_t& getMoveMap() const;
  };
}

#endif

