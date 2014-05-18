#include "GASolver.h"

namespace busybin
{
  /**
   * Initialize the populations.
   * @param numPopulations The total number of populations.
   * @param chromsPerPop This many chromosomes in each population.
   * @param chromLen The lenght of each chromosome in the population.
   * @param cube The RubiksCube.
   */
  GASolver::GASolver(unsigned numPopulations, unsigned chromsPerPop,
    unsigned chromLen, RubiksCube& cube) :
    pCube(&cube), moveStore(cube)
  {
    Random moveRand(0, this->moveStore.getNumMoves() - 1);
    this->numPopulations = numPopulations;
    this->chromsPerPop   = chromsPerPop;
    this->chromLen       = chromLen;

    // Initialize the chromosome populations.
    this->populations.resize(this->numPopulations);

    // Initialize each chromosome.
    for (vector<Chromosome>& chroms : this->populations)
    {
      chroms.reserve(this->chromsPerPop);
     
      for (unsigned i = 0; i < chromsPerPop; ++i)
        chroms.push_back(Chromosome(this->chromLen, moveRand, this->moveStore));
    }
  }

  /**
   * Sove the cube and return the solving chromosome.
   */
  Chromosome GASolver::solve()
  {
    Chromosome* solvedChrom = nullptr;
    Random      selRand(0,   this->chromsPerPop - 1);
    Random      coRand(0,    this->chromLen     - 1);
    Random      probRand(0,  100);
    Random      moveRand(0,  this->moveStore.getNumMoves() - 1);
    Random      popRand(0,   this->numPopulations - 1);
    const unsigned tournSize    = 10;
    const unsigned mutationRate = 3;
    const unsigned migrateEvery = 10000;
    const unsigned numMigrants  = 8;
    const unsigned printEvery   = 10000;
    unsigned       generation   = 0;
    unsigned       bestOfGen;

    while (!solvedChrom)
    {
      bestOfGen = 0;
      for (vector<Chromosome>& chroms : this->populations)
      {
        GASolver::ChromComp cComp;
        PopulationView      popView;

        for (Chromosome& chrom : chroms)
        {
          // Store the cube.  After applying and evaluating all the moves it will
          // be restored using this.
          RubiksCube holdCube = *this->pCube;

          // Reset the fitness.
          chrom.setBestFitness(0);
          chrom.setBestFitnessPos(0);
          chrom.setEndFitness(0);

          // Apply and evaluate every move in the chromosome.
          for (unsigned i = 0; i < chrom.getLength(); ++i)
          {
            unsigned  fitness;
            Evaluator evaluator;

            // Apply the move.
            this->moveStore.getMoveFunc(chrom[i])();

            // Evaluate the move.
            fitness = evaluator.eval(*this->pCube);

            // If the cube is solved.
            if (fitness == 100)
            {
              solvedChrom = &chrom;
              return *solvedChrom;
            }

            // If this fitness is the best fitness, store it.
            if (fitness > chrom.getBestFitness())
            {
              chrom.setBestFitness(fitness);
              chrom.setBestFitnessPos(i);
            }

            // Store the best of generation.
            if (fitness > bestOfGen)
              bestOfGen = fitness;

            // If this is the last move, store the fitness.
            if (i == chrom.getLength() - 1)
              chrom.setEndFitness(fitness);
          }

          // Restore the cube.
          *this->pCube = holdCube;
        }

        // Sort the population by fitness.
        sort(chroms.begin(), chroms.end(), cComp);

        // Print the populations every once in a while.
        if ((generation % printEvery) == 0)
          popView.render(chroms.begin(), chroms.end());

        // Make a new population.  Note that the last always moves on (elitism).
        for (unsigned i = 0; i < this->chromsPerPop - 1; ++i)
        {
          multiset<Chromosome*, GASolver::ChromComp> popSort;
          multiset<Chromosome*>::iterator it;
          unsigned    coPos = coRand.next();
          Chromosome* c1;
          Chromosome* c2;

          // Tournament style - pick three chromosomes from the population.
          for (unsigned j = 0; j < tournSize; ++j)
            popSort.insert(&chroms[selRand.next()]);

          // The best two get crossed over.
          it = popSort.begin();
          c1 = *it;
          c2 = *(++it);

          // Crossover the two chromosomes.
          Chromosome newChrom(*c1);
          /*for (unsigned j = coPos; j < this->chromLen; ++j)
            newChrom[j] = (*c2)[j];*/
          newChrom[coPos] = (*c2)[coPos];

          // Mutate the new chromosome.
          for (unsigned j = 0; j < this->chromLen; ++j)
          {
            if (probRand.next() <= mutationRate)
              newChrom[j] = this->moveStore.getMove(moveRand.next());
          }

          /*ChromosomeView cView;
          cout << "Selected  1: ";
          cView.render(*c1);
          cout << "Selected  2: ";
          cView.render(*c2);
          cout << setw(9) << "coPos " << setw(2) << coPos << ": ";
          cView.render(newChrom);*/

          // Replace the chromosome at i with the new one.
          chroms[i] = newChrom;
        }
      }

      // Migrate.
      if ((generation % migrateEvery) == 0)
      {
        for (unsigned i = 0; i < numMigrants; ++i)
          swap(this->populations[popRand.next()][selRand.next()], this->populations[popRand.next()][selRand.next()]);
      }

      if ((generation % printEvery) == 0)
        cout << "Best of generation: " << bestOfGen << endl;

      ++generation;
    }

    // TODO:
    return this->populations[1][1];
    //return *solvedChrom;
  }

  /**
   * Comparator for chromosomes.  Sorts based on best fitness.  If the best
   * fitness is equal then the best fitness position is used.
   * @param lhs The left side of the comparison.
   * @param rhs The right side of the comparison.
   */
  bool GASolver::ChromComp::operator()(const Chromosome& lhs, const Chromosome& rhs) const
  {
    if (lhs.getBestFitness() == rhs.getBestFitness())
      return lhs.getBestFitnessPos() < rhs.getBestFitnessPos();
    else
      return lhs.getBestFitness() < rhs.getBestFitness();
  }

  /**
   * Comparator for chromosome pointers.  Sorts based on best fitness.  If the
   * best fitness is equal then the best fitness position is used.
   * @param lhs The left side of the comparison.
   * @param rhs The right side of the comparison.
   */
  bool GASolver::ChromComp::operator()(const Chromosome* lhs, const Chromosome* rhs) const
  {
    return (*this)(*lhs, *rhs);
  }
}

