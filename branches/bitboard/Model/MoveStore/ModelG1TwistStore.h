#ifndef _BUSYBIN_MODEL_G1_TWIST_STORE_H_
#define _BUSYBIN_MODEL_G1_TWIST_STORE_H_

#include "TwistStore.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Class for storing the available Rubik's Cube Model's twists in the
   * G1 group.  (This group excluded quarter turns of U and D.)
   */
  class ModelG1TwistStore : public TwistStore
  {
    MoveStore::moveFuncMap_t moveMap;

  protected:
    MoveStore::moveFuncMap_t& getMoveMap();

  public:
    ModelG1TwistStore(RubiksCubeModel& cube);
    const MoveStore::moveFuncMap_t& getMoveMap() const;
  };
}

#endif

