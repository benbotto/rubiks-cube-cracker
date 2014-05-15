#include "ChromosomeView.h"

namespace busybin
{
  /**
   * Init.
   */
  ChromosomeView::ChromosomeView()
  {
  }

  /**
   * Render the cuve.
   * @param chromosome The Chromosome.
   */
  void ChromosomeView::render(const Chromosome& chromosome) const
  {
    for (unsigned i = 0; i < chromosome.getLength(); ++i)
      cout << chromosome[i] << ' ';
    cout << endl;
  }
}

