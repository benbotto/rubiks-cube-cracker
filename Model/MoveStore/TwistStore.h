#ifndef _BUSYBIN_TWIST_STORE_H_
#define _BUSYBIN_TWIST_STORE_H_

#include "MoveStore.h"

namespace busybin
{
  /**
   * Base class for the TwistStore classes.
   */
  class TwistStore : public MoveStore
  {
  private:
    const vector<string> moves;
    const invMove_t      inverseMoves;

  protected:
    virtual moveFuncMap_t& getMoveMap() = 0;

  public:
    TwistStore();
    TwistStore(const vector<string>& moves);

    const vector<string>& getMoves() const;
    const MoveStore::invMove_t& getInverseMoves() const;

    virtual const moveFuncMap_t& getMoveMap() const = 0;
  };
}

#endif

