#ifndef _BUSYBIN_MODEL_ROTATION_STORE_H_
#define _BUSYBIN_MODEL_ROTATION_STORE_H_

#include "RotationStore.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Class for storing the available Rubik's Cube Model's twists.
   */
  class ModelRotationStore : public RotationStore
  {
    MoveStore::moveFuncMap_t moveMap;

  protected:
    MoveStore::moveFuncMap_t& getMoveMap();

  public:
    ModelRotationStore(RubiksCubeModel& cube);
    const MoveStore::moveFuncMap_t& getMoveMap() const;
  };
}

#endif

