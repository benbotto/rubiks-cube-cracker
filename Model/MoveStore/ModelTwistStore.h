#ifndef _BUSYBIN_MODEL_TWIST_STORE_H_
#define _BUSYBIN_MODEL_TWIST_STORE_H_

#include "TwistStore.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Class for storing the available Rubik's Cube Model's twists.
   */
  class ModelTwistStore : public TwistStore
  {
    MoveStore::moveFuncMap_t moveMap;
    RubiksCubeModel* pCube;

  protected:
    MoveStore::moveFuncMap_t& getMoveMap();

  public:
    ModelTwistStore(RubiksCubeModel& cube);
    const MoveStore::moveFuncMap_t& getMoveMap() const;
    void move(uint8_t ind);
    void invert(uint8_t ind);
  };
}

#endif

