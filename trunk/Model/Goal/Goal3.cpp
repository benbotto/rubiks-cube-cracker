#include "Goal3.h"

namespace busybin
{
  /**
   * Solve a 2x2x2 cube.
   * @param cube The cube.
   */
  bool Goal3::isSatisfied(const RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      (this->LU && this->LUF && this->UF && this->LF) ||
      (this->UF && this->RUF && this->RU && this->RF) ||
      (this->RU && this->RUB && this->UB && this->RB) ||
      (this->UB && this->LUB && this->LU && this->LB) ||

      (this->LD && this->LDF && this->DF && this->LF) ||
      (this->DF && this->RDF && this->RD && this->RF) ||
      (this->RD && this->RDB && this->DB && this->RB) ||
      (this->DB && this->LDB && this->LD && this->LB);
  }
}
