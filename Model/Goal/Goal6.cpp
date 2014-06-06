#include "Goal6.h"

namespace busybin
{
  /**
   * Solve a 2x2x3 cube with an additional edges and corner solved.
   * @param cube The cube.
   */
  bool Goal6::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      (this->UF && this->LU && this->UB && this->LF && this->LB && this->DF
      this->LUF && this->LUB
      (this->LU && this->LUF && this->UF && this->LF && this->LD && this->UB && this->DF) ||

      (this->UF && this->RUF && this->RU && this->RF && this->DF  && this->RDF && this->RD) ||
      (this->RU && this->RUB && this->UB && this->RB && this->RD  && this->RDB && this->DB) ||
      (this->UB && this->LUB && this->LU && this->LB && this->DB  && this->LDB && this->LD) ||
      (this->LU && this->LUF && this->UF && this->LF && this->UB  && this->LUB && this->LB) ||
      (this->UF && this->RUF && this->RU && this->RF && this->RUB && this->UB  && this->RB) ||
      (this->LD && this->LDF && this->DF && this->LF && this->DB  && this->LDB && this->LB) ||
      (this->DF && this->RDF && this->RD && this->RF && this->RDB && this->DB  && this->RB);
  }
}
