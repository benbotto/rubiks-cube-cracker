#include "Goal6.h"

namespace busybin
{
  /**
   * Solve a 2x2x3 cube with an adjacent edge/corner solved.
   * @param cube The cube.
   */
  bool Goal6::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    // 32 cases.  8 ways of solving a 2x2x3, with 4 ways of solving
    // and adjacent edge/corner per.
    return
      // 2x2x3 in the upper left.
      (this->LUB && this->UB && this->LU && this->LUF && this->UF && this->LB && this->LF && this->LDB && this->DB) ||
      (this->LUB && this->UB && this->LU && this->LUF && this->UF && this->LB && this->LF && this->LDF && this->DF) ||
      (this->LUB && this->UB && this->LU && this->LUF && this->UF && this->LB && this->LF && this->RUF && this->RF) ||
      (this->LUB && this->UB && this->LU && this->LUF && this->UF && this->LB && this->LF && this->RUB && this->RB) ||

      // 2x2x3 in the upper right.
      (this->RUB && this->UB && this->RU && this->RUF && this->UF && this->RB && this->RF && this->RDB && this->DB) ||
      (this->RUB && this->UB && this->RU && this->RUF && this->UF && this->RB && this->RF && this->RDF && this->DF) ||
      (this->RUB && this->UB && this->RU && this->RUF && this->UF && this->RB && this->RF && this->LUB && this->LB) ||
      (this->RUB && this->UB && this->RU && this->RUF && this->UF && this->RB && this->RF && this->LUF && this->LF) ||

      // 2x2x3 in the bottom right.
      (this->RDB && this->DB && this->RD && this->RDF && this->DF && this->RB && this->RF && this->RUB && this->UB) ||
      (this->RDB && this->DB && this->RD && this->RDF && this->DF && this->RB && this->RF && this->RUF && this->UF) ||
      (this->RDB && this->DB && this->RD && this->RDF && this->DF && this->RB && this->RF && this->LDF && this->LF) ||
      (this->RDB && this->DB && this->RD && this->RDF && this->DF && this->RB && this->RF && this->LDB && this->LB) ||

      // 2x2x3 in the bottom left.
      (this->LDB && this->DB && this->LD && this->LDF && this->DF && this->LB && this->LF && this->LUB && this->UB) ||
      (this->LDB && this->DB && this->LD && this->LDF && this->DF && this->LB && this->LF && this->LUF && this->UF) ||
      (this->LDB && this->DB && this->LD && this->LDF && this->DF && this->LB && this->LF && this->RDF && this->RF) ||
      (this->LDB && this->DB && this->LD && this->LDF && this->DF && this->LB && this->LF && this->RDB && this->RB) ||

      // 2x2x3 in the front left.
      (this->LU && this->LUF && this->UF && this->LF && this->LD && this->LDF && this->DF && this->RUF && this->RU) ||
      (this->LU && this->LUF && this->UF && this->LF && this->LD && this->LDF && this->DF && this->RDF && this->RD) ||
      (this->LU && this->LUF && this->UF && this->LF && this->LD && this->LDF && this->DF && this->LUB && this->UB) ||
      (this->LU && this->LUF && this->UF && this->LF && this->LD && this->LDF && this->DF && this->LDB && this->DB) ||

      // 2x2x3 in the front right.
      (this->RU && this->RUF && this->UF && this->RF && this->RD && this->RDF && this->DF && this->LUF && this->LU) ||
      (this->RU && this->RUF && this->UF && this->RF && this->RD && this->RDF && this->DF && this->LDF && this->LD) ||
      (this->RU && this->RUF && this->UF && this->RF && this->RD && this->RDF && this->DF && this->RUB && this->UB) ||
      (this->RU && this->RUF && this->UF && this->RF && this->RD && this->RDF && this->DF && this->RDB && this->DB) ||

      // 2x2x3 in the back right.
      (this->RU && this->RUB && this->UB && this->RB && this->RD && this->RDB && this->DB && this->LUB && this->LU) ||
      (this->RU && this->RUB && this->UB && this->RB && this->RD && this->RDB && this->DB && this->LDB && this->LD) ||
      (this->RU && this->RUB && this->UB && this->RB && this->RD && this->RDB && this->DB && this->RUF && this->UF) ||
      (this->RU && this->RUB && this->UB && this->RB && this->RD && this->RDB && this->DB && this->RDF && this->DF) ||

      // 2x2x3 in the back left.
      (this->LU && this->LUB && this->UB && this->LB && this->LD && this->LDB && this->DB && this->LUF && this->UF) ||
      (this->LU && this->LUB && this->UB && this->LB && this->LD && this->LDB && this->DB && this->LDF && this->DF) ||
      (this->LU && this->LUB && this->UB && this->LB && this->LD && this->LDB && this->DB && this->RUB && this->RU) ||
      (this->LU && this->LUB && this->UB && this->LB && this->LD && this->LDB && this->DB && this->RDB && this->RD);
  }
}
