#include "RubiksCubeController.h"

namespace busybin
{
  /**
   * Initialize.
   */
  RubiksCubeController::RubiksCubeController() : moveStore(this->cube),
    scrambler(this->cube, this->moveStore, this->cubeView),
    rand(0, this->moveStore.getNumMoves() - 1)
  {
    const unsigned numPopulations = 40;
    const unsigned chromsPerPop   = 100;
    const unsigned chromLen       = 30;

    // Initialize the populations.
    this->populations.resize(numPopulations);

    // Initialize each chromosome.
    for (vector<Chromosome>& chroms : this->populations)
    {
      chroms.reserve(chromsPerPop);
     
      for (unsigned i = 0; i < chromsPerPop; ++i)
        chroms.push_back(Chromosome(chromLen, this->rand, this->moveStore));
    }
  }

  /**
   * Main game loop.
   */
  void RubiksCubeController::start()
  {
    // Let the user scramble the cube.
    this->scrambler.manualScramble();

    for (vector<Chromosome>& chroms : this->populations)
    {
      for (Chromosome& chrom : chroms)
      {
        RubiksCube hold = this->cube;

        for (unsigned i = 0; i < chrom.getLength(); ++i)
        {
          this->moveStore.getMoveFunc(chrom[i])();
          cout << this->evaluator.eval(this->cube) << endl;
        }

        this->cube = hold;
      }

      this->cubeView.render(this->cube);
    }
  }
}

