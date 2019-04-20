#include "EdgeG1PatternDatabase.h"
#include <iostream>
using std::cout;
using std::endl;

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG1PatternDatabase::getDatabaseIndex(const RubiksCubeModel& cube) const
  {
    char colors[] = {'W', 'G', 'R', 'B', 'O', 'Y'};

    // UB RY 0.
    edge_t ub =
    {
      cube.get(F::UP,   0, 1),
      cube.get(F::BACK, 0, 1)
    };

    cout << colors[(unsigned)ub[0]] << colors[(unsigned)ub[1]]
         << ' ' << (unsigned)this->getCubieIndex(ub) << endl;

    // UR RG 1.
    edge_t ur =
    {
      cube.get(F::UP,    1, 2),
      cube.get(F::RIGHT, 0, 1)
    };

    cout << colors[(unsigned)ur[0]] << colors[(unsigned)ur[1]]
         << ' ' << (unsigned)this->getCubieIndex(ur) << endl;

    // UF RW 2.
    edge_t uf =
    {
      cube.get(F::UP,    2, 1),
      cube.get(F::FRONT, 0, 1)
    };

    cout << colors[(unsigned)uf[0]] << colors[(unsigned)uf[1]]
         << ' ' << (unsigned)this->getCubieIndex(uf) << endl;

    // UL RB 3.
    edge_t ul =
    {
      cube.get(F::UP,   1, 0),
      cube.get(F::LEFT, 0, 1)
    };

    cout << colors[(unsigned)ul[0]] << colors[(unsigned)ul[1]]
         << ' ' << (unsigned)this->getCubieIndex(ul) << endl;

    // FR WG 4.
    edge_t fr =
    {
      cube.get(F::FRONT, 1, 2),
      cube.get(F::RIGHT, 1, 0)
    };

    cout << colors[(unsigned)fr[0]] << colors[(unsigned)fr[1]]
         << ' ' << (unsigned)this->getCubieIndex(fr) << endl;

    // FL WB 5.
    edge_t fl =
    {
      cube.get(F::FRONT, 1, 0),
      cube.get(F::LEFT,  1, 2)
    };

    cout << colors[(unsigned)fl[0]] << colors[(unsigned)fl[1]]
         << ' ' << (unsigned)this->getCubieIndex(fl) << endl;

    perm_t edgePerm =
    {
      this->getCubieIndex(ub),
      this->getCubieIndex(ur),
      this->getCubieIndex(uf),
      this->getCubieIndex(ul),
      this->getCubieIndex(fr),
      this->getCubieIndex(fl)
    };

    cout << "Edge permutation: ";
    for (unsigned i: edgePerm)
      cout << i << ' ';
    cout << endl;

    // Now get the orientation of each edge.
    array<uchar, 6> edgeOrientations =
    {
      this->getCubieOrientation(ub),
      this->getCubieOrientation(ur),
      this->getCubieOrientation(uf),
      this->getCubieOrientation(ul),
      this->getCubieOrientation(fr),
      this->getCubieOrientation(fl)
    };

    cout << "Edge orientation: ";
    for (unsigned i: edgeOrientations)
      cout << i << ' ';
    cout << endl;

    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

