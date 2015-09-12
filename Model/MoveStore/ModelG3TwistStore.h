#ifndef _BUSYBIN_MODEL_G3_TWIST_STORE_H_
#define _BUSYBIN_MODEL_G3_TWIST_STORE_H_

#include "TwistStore.h"
#include "../RubiksCubeModel.h"

namespace busybin
{
  /**
   * Class for storing the available Rubik's Cube Model's twists in the
   * G3 group.  <L2,R2,F2,B2,U2,D2>
   */
  class ModelG3TwistStore : public TwistStore
  {
    MoveStore::moveFuncMap_t moveMap;

  protected:
    MoveStore::moveFuncMap_t& getMoveMap();

  public:
    ModelG3TwistStore(RubiksCubeModel& cube);
    const MoveStore::moveFuncMap_t& getMoveMap() const;
  };
}

#endif

