#include "Chromosome.h"

namespace busybin
{
  /**
   * Initialize the chromosome.
   * @param length The length of the chromosome.
   * @param rand A random generator for generating moves.
   * @param moveStore A MoveStore for generating moves.
   */
  Chromosome::Chromosome(unsigned length, Random& rand,
    const MoveStore& moveStore)
  {
    this->length     = length;
    this->endFitness = this->bestFitness = this->bestFitnessPos = 0;

    for (unsigned i = 0; i < length; ++i)
      this->bases.push_back(moveStore.getMove(rand.next()));
  }

  /**
   * Get the base (move) at pos.  Checked.
   * @param pos The index.
   */
  string& Chromosome::at(unsigned pos)
  {
    if (pos >= this->length)
      throw RubiksCubeException("Position out of bounds.");

    return this->bases[pos];
  }

  /**
   * Get the base (move) at pos.  Checked.
   * @param pos The index.
   */
  const string& Chromosome::at(unsigned pos) const
  {
    if (pos >= this->length)
      throw RubiksCubeException("Position out of bounds.");

    return this->bases[pos];
  }

  /**
   * Get the base (move) at pos.  Unchecked.
   * @param pos The index.
   */
  string& Chromosome::operator[](unsigned pos)
  {
    return this->bases[pos];
  }

  /**
   * Get the base (move) at pos.  Unchecked.
   * @param pos The index.
   */
  const string& Chromosome::operator[](unsigned pos) const
  {
    return this->bases[pos];
  }

  /**
   * Get the beginning gene (move) for iteration.
   */
  Iterator<string> Chromosome::begin()
  {
    return Iterator<string>(*this, 0);
  }

  /**
   * Get the beginning gene (move) for iteration.
   */
  ConstIterator<string> Chromosome::begin() const
  {
    return ConstIterator<string>(*this, 0);
  }

  /**
   * Get one past the last gene (move) for iteration.
   */
  Iterator<string> Chromosome::end()
  {
    return Iterator<string>(*this, this->bases.size());
  }

  /**
   * Get one past the last gene (move) for iteration.
   */
  ConstIterator<string> Chromosome::end() const
  {
    return ConstIterator<string>(*this, this->bases.size());
  }

  /**
   * Get the length of the chromosome.
   */
  unsigned Chromosome::getLength() const
  {
    return this->length;
  }

  /**
   * Get the best fitness.  The cube might have been in a great
   * position after two turns, but terrible at the end, for example.
   */
  unsigned Chromosome::getBestFitness() const
  {
    return this->bestFitness;
  }

  /**
   * Set the best fitness.
   * @param fitness The new fitness value.
   */
  void Chromosome::setBestFitness(unsigned fitness)
  {
    this->bestFitness = fitness;
  }

  /**
   * Get the position at which the fitness was the best.
   */
  unsigned Chromosome::getBestFitnessPos() const
  {
    return this->bestFitnessPos;
  }

  /**
   * Set the best fitness position.
   * @param pos The position in the chromosome that had the best fitness.
   */
  void Chromosome::setBestFitnessPos(unsigned pos)
  {
    if (pos >= this->length)
      throw RubiksCubeException("Position out of bounds.");

    this->bestFitnessPos = pos;
  }

  /**
   * Get the fitness at the end of the chromosome.
   */
  unsigned Chromosome::getEndFitness() const
  {
    return this->endFitness;
  }

  /**
   * Set the fitness at the end of the chromosome.
   * @param fitness The end fitness.
   */
  void Chromosome::setEndFitness(unsigned fitness)
  {
    this->endFitness = fitness;
  }
}

