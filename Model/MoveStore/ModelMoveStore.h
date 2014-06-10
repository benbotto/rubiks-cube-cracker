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
    MoveStore::rotMap_t  rotMap;

  protected:
    MoveStore::moveMap_t& getMoveMap();
    MoveStore::rotMap_t&  getRotationMap();

  public:
    ModelMoveStore(RubiksCubeModel& cube);
    const MoveStore::moveMap_t& getMoveMap() const;
    const MoveStore::rotMap_t& getRotationMap() const;
  };
}

#endif

