#include "Goal6.h"

namespace busybin
{
  /**
   * Solve a 2x2x3 cube with an additional edge solved.
   * @param cube The cube.
   */
  bool Goal6::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      (this->LU && this->LUF && this->UF && this->LF && this->LD  && this->LDF
        && this->DF && (this->RF || this->LB)) ||
      (this->UF && this->RUF && this->RU && this->RF && this->DF  && this->RDF
        && this->RD && (this->LF || this->RB)) ||
      (this->RU && this->RUB && this->UB && this->RB && this->RD  && this->RDB
        && this->DB && (this->RF || this->LB)) ||
      (this->UB && this->LUB && this->LU && this->LB && this->DB  && this->LDB
        && this->LD && (this->LF || this->RB)) ||
      (this->LU && this->LUF && this->UF && this->LF && this->UB  && this->LUB
        && this->LB && (this->RU || this->LD)) ||
      (this->UF && this->RUF && this->RU && this->RF && this->RUB && this->UB
        && this->RB && (this->RD || this->LU)) ||
      (this->LD && this->LDF && this->DF && this->LF && this->DB  && this->LDB
        && this->LB && (this->RD || this->LU)) ||
      (this->DF && this->RDF && this->RD && this->RF && this->RDB && this->DB
        && this->RB && (this->RU || this->LD));
  }
}
