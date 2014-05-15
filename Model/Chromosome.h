#ifndef _BUSYBIN_CHROMOSOME_H_
#define _BUSYBIN_CHROMOSOME_H_

#include "MoveStore.h"
#include "../Util/Random.h"
#include "../Util/RubiksCubeException.h"
#include <string>
using std::string;
#include <vector>
using std::vector;

namespace busybin
{
  /**
   * A "chromosome" is a series of Rubik's Cube moves.
   */
  class Chromosome
  {
    unsigned       length;
    unsigned       bestFitness;
    unsigned       bestFitnessPos;
    unsigned       endFitness;
    vector<string> bases;

  public:
    Chromosome(unsigned length, Random& rand, const MoveStore& moveStore);

    string& at(unsigned pos);
    const string& at(unsigned pos) const;
    string& operator[](unsigned pos);
    const string& operator[](unsigned pos) const;

    unsigned getLength() const;
    unsigned getBestFitness() const;
    void setBestFitness(unsigned fitness);
    unsigned getBestFitnessPos() const;
    void setBestFitnessPos(unsigned pos);
    unsigned getEndFitness() const;
    void setEndFitness(unsigned fitness);
  };
}

#endif

