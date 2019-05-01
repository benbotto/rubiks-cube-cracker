#ifndef _BUSYBIN_MODEL_G2_TWIST_STORE_H_
#define _BUSYBIN_MODEL_G2_TWIST_STORE_H_

#include "TwistStore.h"
#include "../RubiksCubeModel.h"
#include <array>
using std::array;

namespace busybin
{
  /**
   * Class for storing the available Rubik's Cube Model's twists in the
   * G2 group.  <L,R,F2,B2,U2,D2>
   */
  class ModelG2TwistStore : public TwistStore
  {
    MoveStore::moveFuncMap_t moveMap;
    RubiksCubeModel* pCube;
    array<RubiksCubeModel::MOVE, 6> moveInds;

  protected:
    MoveStore::moveFuncMap_t& getMoveMap();

  public:
    ModelG2TwistStore(RubiksCubeModel& cube);
    const MoveStore::moveFuncMap_t& getMoveMap() const;

    void move(uint8_t ind);
    void invert(uint8_t ind);
  };
}

#endif

