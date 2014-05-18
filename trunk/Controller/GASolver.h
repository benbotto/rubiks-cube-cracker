#ifndef _BUSYBIN_GA_SOLVER_H_
#define _BUSYBIN_GA_SOLVER_H_

#include "Evaluator.h"
#include "../Model/MoveStore.h"
#include "../Model/Chromosome.h"
#include "../View/PopulationView.h"
#include "../Util/Random.h"
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
#include <set>
using std::multiset;
#include <iterator>
using std::prev;
#include <algorithm>
using std::swap;

namespace busybin
{
  /**
   * Class for solving the cube genetically.
   */
  class GASolver
  {
    typedef vector<Chromosome>   population_t;
    typedef vector<population_t> populations_t;

    unsigned       numPopulations;
    unsigned       chromsPerPop;
    unsigned       chromLen;
    RubiksCube*    const pCube;
    MoveStore      moveStore;
    populations_t  populations;

    /**
     * Used for sorting populations.
     */
    class ChromComp
    {
    public:
      bool operator()(const Chromosome& lhs, const Chromosome& rhs) const;
      bool operator()(const Chromosome* lhs, const Chromosome* rhs) const;
    };

  public:
    GASolver(unsigned numPopulations, unsigned chromsPerPop,
      unsigned chromLen, RubiksCube& cube);
    void crossover(Chromosome& c1, Chromosome& c2) const;
    
    Chromosome solve();
  };
}

#endif

