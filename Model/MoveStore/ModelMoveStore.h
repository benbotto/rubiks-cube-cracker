#ifndef _BUSYBIN_MODEL_MOVE_STORE_H_
#define _BUSYBIN_MODEL_MOVE_STORE_H_

#include "MoveStore.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Class for storing the available Rubik's Cube Model's moves.
   */
  class ModelMoveStore : public MoveStore
  {
    MoveStore::moveMap_t moveMap;

  protected:
    MoveStore::moveMap_t& getMoveMap();

  public:
    ModelMoveStore(RubiksCubeModel& cube);
    const MoveStore::moveMap_t& getMoveMap() const;
  };
}

#endif

