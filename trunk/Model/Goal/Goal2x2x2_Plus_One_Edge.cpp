#include "Goal2x2x2_Plus_One_Edge.h"

namespace busybin
{
  /**
   * Solve a 2x2x2 cube with an additional edge.
   * @param cube The cube.
   */
  bool Goal2x2x2_Plus_One_Edge::isSatisfied(RubiksCubeModel& cube)
  {
    this->updateSolved(cube);

    return
      (this->LU && this->LUF && this->UF && this->LF && this->LDF && (this->LD || this->DF)) ||
      (this->UF && this->RUF && this->RU && this->RF && this->RDF && (this->DF || this->RD)) ||
      (this->RU && this->RUB && this->UB && this->RB && this->RDB && (this->DB || this->RD)) ||
      (this->UB && this->LUB && this->LU && this->LB && this->LDB && (this->LD || this->DB)) ||
      (this->LU && this->LUF && this->UF && this->LF && this->LUB && (this->LB || this->UB)) ||
      (this->UF && this->RUF && this->RU && this->RF && this->RUB && (this->UB || this->RB)) ||
      (this->LD && this->LDF && this->DF && this->LF && this->LDB && (this->DB || this->LB)) ||
      (this->DF && this->RDF && this->RD && this->RF && this->RDB && (this->DB || this->RB));
  }

  /**
   * Describe the goal.
   */
  string Goal2x2x2_Plus_One_Edge::getDescription() const
  {
    return "Solve a 2x2x2 cube with an additional edge.";
  }
}
