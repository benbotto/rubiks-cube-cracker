#include "ChromosomeGenerator.h"

namespace busybin
{
  /**
   * Initialize the generator.
   */
  ChromosomeGenerator::ChromosomeGenerator() :
    moves({{"L", "L'", "L2", "R", "R'", "R2", "U", "U'", "U2", 
            "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2"}}),
    moveDist(0, 17)

  {
    this->generator.seed(system_clock::now().time_since_epoch().count());
  }

  /**
   * Generate a single chromosome.
   * @param size The number of moves in the chromosome.
   */
  vector<string> ChromosomeGenerator::generateChromosome(unsigned size)
  {
    vector<string> chromosome;
    chromosome.reserve(size);

    for (unsigned i = 0; i < size; ++i)
      chromosome.push_back(this->moves.at(this->moveDist(this->generator)));

    return chromosome;
  }
}

