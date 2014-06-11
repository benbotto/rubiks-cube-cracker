#include "Goal2x2x3_1x2x2.h"

namespace busybin
{
  /**
   * Solve 2 layers and an adjacent 1x2x2.
   * @param cube The cube.
   */
  bool Goal2x2x3_1x2x2::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    // There are 24 cases, 4 per face.  Each of the below has two layers 
    // solved except for an adjacent corner and edge.
    return
      // Bottom unsolved.
      (             this->UB && this->RUB && this->LU && this->RU && this->LUF && this->UF && this->RUF &&
                    this->LF && this->RF  && this->RB) ||
      (this->LUB && this->UB &&              this->LU && this->RU && this->LUF && this->UF && this->RUF &&
       this->LB  && this->LF && this->RF             ) ||
      (this->LUB && this->UB && this->RUB && this->LU && this->RU && this->LUF && this->UF &&
       this->LB  && this->LF &&              this->RB) ||
      (this->LUB && this->UB && this->RUB && this->LU && this->RU &&              this->UF && this->RUF &&
       this->LB  &&             this->RF  && this->RB) ||

      // Top unsolved.
      (             this->LF && this->RF  && this->RB &&
                    this->DB && this->RDB && this->LD && this->RD && this->LDF && this->DF && this->RDF) ||
      (this->LB  && this->LF && this->RF  &&
       this->LDB && this->DB &&              this->LD && this->RD && this->LDF && this->DF && this->RDF) ||
      (this->LB  && this->LF &&              this->RB &&
       this->LDB && this->DB && this->RDB && this->LD && this->RD && this->LDF && this->DF             ) ||
      (this->LB  &&             this->RF  && this->RB &&
       this->LDB && this->DB && this->RDB && this->LD && this->RD &&              this->DF && this->RDF) ||

      // Right unsolved.
      (             this->LU && this->LUF && this->LB && this->LF && this->LDB && this->LD && this->LDF &&
                    this->UF && this->DB  && this->DF) ||
      (this->LUB && this->LU && this->LUF && this->LB && this->LF &&              this->LD && this->LDF &&
       this->UB  && this->UF &&              this->DF) ||
      (this->LUB && this->LU && this->LUF && this->LB && this->LF && this->LDB && this->LD &&
       this->UB  && this->UF && this->DB             ) ||
      (this->LUB && this->LU &&              this->LB && this->LF && this->LDB && this->LD && this->LDF &&
       this->UB  &&             this->DB  && this->DF) ||

      // Left unsolved.
      (             this->UF && this->DB  && this->DF &&
                    this->RU && this->RUF && this->RB && this->RF && this->RDB && this->RD && this->RDF) ||
      (this->UB  && this->UF &&              this->DF &&
       this->RUB && this->RU && this->RUF && this->RB && this->RF &&              this->RD && this->RDF) ||
      (this->UB  && this->UF && this->DB  &&
       this->RUB && this->RU && this->RUF && this->RB && this->RF && this->RDB && this->RD             ) ||
      (this->UB  &&             this->DB  && this->DF &&
       this->RUB && this->RU &&              this->RB && this->RF && this->RDB && this->RD && this->RDF) ||

      // Back unsolved.
      (             this->UF && this->RUF && this->LF && this->RF && this->LDF && this->DF && this->RDF &&
                    this->RU && this->LD  && this->RD) ||
      (this->LUF && this->UF &&              this->LF && this->RF && this->LDF && this->DF && this->RDF &&
       this->LU  &&             this->LD  && this->RD) ||
      (this->LUF && this->UF && this->RUF && this->LF && this->RF && this->LDF && this->DF &&
       this->LU  && this->RU && this->LD             ) ||
      (this->LUF && this->UF && this->RUF && this->LF && this->RF &&              this->DF && this->RDF &&
       this->LU  && this->RU &&              this->RD) ||

      // Front unsolved.
      (             this->RU && this->LD  && this->RD &&
                    this->UB && this->RUB && this->LB && this->RB && this->LDB && this->DB && this->RDB) ||
      (this->LU  &&             this->LD  && this->RD &&
       this->LUB && this->UB &&              this->LB && this->RB && this->LDB && this->DB && this->RDB) ||
      (this->LU  && this->RU && this->LD  &&
       this->LUB && this->UB && this->RUB && this->LB && this->RB && this->LDB && this->DB             ) ||
      (this->LU  && this->RU &&              this->RD &&
       this->LUB && this->UB && this->RUB && this->LB && this->RB &&              this->DB && this->RDB);
  }

  /**
   * Describe the goal.
   */
  string Goal2x2x3_1x2x2::getDescription() const
  {
    return "Solve 2 layers and an adjacent 1x2x2.";
  }
}
