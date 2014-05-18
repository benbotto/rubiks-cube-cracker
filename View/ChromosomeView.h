#ifndef _BUSYBIN_CHROMOSOME_VIEW_H_
#define _BUSYBIN_CHROMOSOME_VIEW_H_

#include "../Model/Chromosome.h"
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;

namespace busybin
{
  /**
   * Console view for a Chromosome.
   */
  class ChromosomeView
  {
  public:
    ChromosomeView();
    void render(const Chromosome& chromosome) const;
  };
}

#endif

