#include "Goal2.h"

namespace busybin
{
  /**
   * Check if an adjacent edge is solved.
   * @param cube The cube.
   */
  bool Goal2::isSatisfied(const RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      (this->LU && this->UF) ||
      (this->LU && this->UB) ||
      (this->LU && this->LF) ||
      (this->LU && this->LB) ||

      (this->RU && this->UF) ||
      (this->RU && this->UB) ||
      (this->RU && this->RF) ||
      (this->RU && this->RB) ||

      (this->LD && this->DF) ||
      (this->LD && this->DB) ||
      (this->LD && this->LF) ||
      (this->LD && this->LB) ||

      (this->RD && this->DF) ||
      (this->RD && this->DB) ||
      (this->RD && this->RF) ||
      (this->RD && this->RB);
  }
}
