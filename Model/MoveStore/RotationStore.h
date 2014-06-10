#ifndef _BUSYBIN_ROTATION_STORE_H_
#define _BUSYBIN_ROTATION_STORE_H_

#include "MoveStore.h"

namespace busybin
{
  /**
   * Base class for the RotationStore classes.
   */
  class RotationStore : public MoveStore
  {
  private:
    const vector<string> moves;
    const invMove_t      inverseMoves;

  protected:
    virtual moveFuncMap_t& getMoveMap() = 0;

  public:
    RotationStore();

    const vector<string>& getMoves() const;
    const MoveStore::invMove_t& getInverseMoves() const;
    unsigned getNumMoves() const;

    virtual const moveFuncMap_t& getMoveMap() const = 0;
  };
}

#endif

