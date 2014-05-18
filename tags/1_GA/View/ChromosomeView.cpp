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
    for (const string& move : chromosome)
      cout << setw(2) << move << ' ';
    cout << endl;
  }
}

