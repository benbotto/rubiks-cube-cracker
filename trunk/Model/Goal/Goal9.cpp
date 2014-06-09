#include "Goal9.h"

namespace busybin
{
  /**
   * Solve 2 layers except for one corner/edge.  All edges solved.
   * @param cube The cube.
   */
  bool Goal9::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      this->goal7.isSatisfied(cube) &&
      this->LU && this->LF && this->LB && this->LD && this->DF && this->DB && 
      this->UF && this->UB && this->RU && this->RF && this->RB && this->RD;
  }
}
