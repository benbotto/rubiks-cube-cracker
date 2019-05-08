#include "RubiksCube.h"

namespace busybin
{
  /**
   * Move using a move index.
   */
  RubiksCube& RubiksCube::move(MOVE ind)
  {
    switch (ind)
    {
      case MOVE::L:
        return this->l();
      case MOVE::LPRIME:
        return this->lPrime();
      case MOVE::L2:
        return this->l2();
      case MOVE::R:
        return this->r();
      case MOVE::RPRIME:
        return this->rPrime();
      case MOVE::R2:
        return this->r2();
      case MOVE::U:
        return this->u();
      case MOVE::UPRIME:
        return this->uPrime();
      case MOVE::U2:
        return this->u2();
      case MOVE::D:
        return this->d();
      case MOVE::DPRIME:
        return this->dPrime();
      case MOVE::D2:
        return this->d2();
      case MOVE::F:
        return this->f();
      case MOVE::FPRIME:
        return this->fPrime();
      case MOVE::F2:
        return this->f2();
      case MOVE::B:
        return this->b();
      case MOVE::BPRIME:
        return this->bPrime();
      case MOVE::B2:
        return this->b2();
      case MOVE::Y:
        return this->y();
      case MOVE::YPRIME:
        return this->yPrime();
      case MOVE::Y2:
        return this->y2();
      case MOVE::X:
        return this->x();
      case MOVE::XPRIME:
        return this->xPrime();
      case MOVE::X2:
        return this->x2();
      case MOVE::Z:
        return this->z();
      case MOVE::ZPRIME:
        return this->zPrime();
      case MOVE::Z2:
        return this->z2();
      default:
        throw RubiksCubeException("Invalid face turn index.");
    }
  }

  /**
   * Invert a move.
   * @param ind The move index.  The inverse will be applied.
   */
  RubiksCube& RubiksCube::invert(MOVE ind)
  {
    switch (ind)
    {
      case MOVE::L:
        return this->lPrime();
      case MOVE::LPRIME:
        return this->l();
      case MOVE::L2:
        return this->l2();
      case MOVE::R:
        return this->rPrime();
      case MOVE::RPRIME:
        return this->r();
      case MOVE::R2:
        return this->r2();
      case MOVE::U:
        return this->uPrime();
      case MOVE::UPRIME:
        return this->u();
      case MOVE::U2:
        return this->u2();
      case MOVE::D:
        return this->dPrime();
      case MOVE::DPRIME:
        return this->d();
      case MOVE::D2:
        return this->d2();
      case MOVE::F:
        return this->fPrime();
      case MOVE::FPRIME:
        return this->f();
      case MOVE::F2:
        return this->f2();
      case MOVE::B:
        return this->bPrime();
      case MOVE::BPRIME:
        return this->b();
      case MOVE::B2:
        return this->b2();
      case MOVE::Y:
        return this->yPrime();
      case MOVE::YPRIME:
        return this->y();
      case MOVE::Y2:
        return this->y2();
      case MOVE::X:
        return this->xPrime();
      case MOVE::XPRIME:
        return this->x();
      case MOVE::X2:
        return this->x2();
      case MOVE::Z:
        return this->zPrime();
      case MOVE::ZPRIME:
        return this->z();
      case MOVE::Z2:
        return this->z2();
      default:
        throw RubiksCubeException("Invalid face turn index.");
    }
  }
}

