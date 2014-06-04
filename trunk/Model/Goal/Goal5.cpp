#include "Goal5.h"

namespace busybin
{
  /**
   * Solve a 2x2x3 cube.
   * @param cube The cube.
   */
  bool Goal5::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      (this->LU && this->LUF && this->UF && this->LF && this->LD  && this->LDF && this->DF) ||
      (this->UF && this->RUF && this->RU && this->RF && this->DF  && this->RDF && this->RD) ||
      (this->RU && this->RUB && this->UB && this->RB && this->RD  && this->RDB && this->DB) ||
      (this->UB && this->LUB && this->LU && this->LB && this->DB  && this->LDB && this->LD) ||
      (this->LU && this->LUF && this->UF && this->LF && this->UB  && this->LUB && this->LB) ||
      (this->UF && this->RUF && this->RU && this->RF && this->RUB && this->UB  && this->RB) ||
      (this->LD && this->LDF && this->DF && this->LF && this->DB  && this->LDB && this->LB) ||
      (this->DF && this->RDF && this->RD && this->RF && this->RDB && this->DB  && this->RB);
  }
}
