#include "Goal1.h"

namespace busybin
{
  /**
   * Check if any edge is solved.
   * @param cube The cube.
   */
  bool Goal1::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      this->LU  ||
      this->UF  ||
      this->RU  ||
      this->UB  ||
      this->LF  ||
      this->RF  ||
      this->RB  ||
      this->LB  ||
      this->LD  ||
      this->DF  ||
      this->RD  ||
      this->DB;
  }
}
