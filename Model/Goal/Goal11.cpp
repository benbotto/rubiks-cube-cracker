#include "Goal11.h"

namespace busybin
{
  /**
   * Solve 2 layers.
   * @param cube The cube.
   */
  bool Goal11::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      /*(this->LU && this->LF && this->LB && this->LD && this->DF && this->DB && 
       this->UF && this->UB && this->RU && this->RF && this->RB && this->RD) &&*/
      (
        // Bottom unsolved.
        (this->LUB && this->UB && this->RUB && this->LU && this->RU && this->LUF && this->UF && this->RUF &&
         this->LB  && this->LF && this->RF  && this->RB) ||

        // Top unsolved.
        (this->LB  && this->LF && this->RF  && this->RB &&
         this->LDB && this->DB && this->RDB && this->LD && this->RD && this->LDF && this->DF && this->RDF) ||

        // Right unsolved.
        (this->LUB && this->LU && this->LUF && this->LB && this->LF && this->LDB && this->LD && this->LDF &&
         this->UB  && this->UF && this->DB  && this->DF) ||

        // Left unsolved.
        (this->UB  && this->UF && this->DB  && this->DF &&
         this->RUB && this->RU && this->RUF && this->RB && this->RF && this->RDB && this->RD && this->RDF) ||

        // Back unsolved.
        (this->LUF && this->UF && this->RUF && this->LF && this->RF && this->LDF && this->DF && this->RDF &&
         this->LU  && this->RU && this->LD  && this->RD) ||

        // Front unsolved.
        (this->LU  && this->RU && this->LD  && this->RD &&
         this->LUB && this->UB && this->RUB && this->LB && this->RB && this->LDB && this->DB && this->RDB)
      );
  }
}
