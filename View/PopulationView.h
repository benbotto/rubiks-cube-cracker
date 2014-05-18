#ifndef _BUSYBIN_POPULATION_VIEW_H_
#define _BUSYBIN_POPULATION_VIEW_H_

#include "ChromosomeView.h"
#include "../Model/Chromosome.h"
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
using std::left;
using std::right;
using std::setfill;

namespace busybin
{
  /**
   * Console view for a Population of Chromosome.
   */
  class PopulationView
  {
  public:
    /**
     * Print the population.
     * @param begin An iterator to the beginning of the population.
     * @param end An iterator to the beginning of the population.
     */
    template <typename Iterator>
    void render(Iterator begin, Iterator end) const
    {
      ChromosomeView chromView;

      cout << left
           << setw(14)     << "Best Fitness"
           << setw(10)     << "Position"
           << setw(13)     << "End Fitness"
           << setw(90)     << "Chromosome"
           << right        << '\n'
           << setfill('-') << setw(127) << '\n'
           << setfill(' ');

      while (begin != end)
      {
        cout << left
             << setw(14) << begin->getBestFitness()
             << setw(10) << begin->getBestFitnessPos()
             << setw(13) << begin->getEndFitness();
        chromView.render(*begin);
        ++begin;
      }
      cout << endl;
    }
  };
}

#endif

