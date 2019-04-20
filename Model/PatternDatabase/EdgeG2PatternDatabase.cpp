#include "EdgeG2PatternDatabase.h"
#include <iostream>
using std::cout;
using std::endl;

namespace busybin
{
  /**
   * Given a cube, get an index into the pattern database.
   */
  uint32_t EdgeG2PatternDatabase::getDatabaseIndex(const RubiksCubeModel& cube) const
  {
    char colors[] = {'W', 'G', 'R', 'B', 'O', 'Y'};

    // BL YB 6.
    edge_t bl =
    {
      cube.get(F::BACK, 1, 2),
      cube.get(F::LEFT, 1, 0)
    };

    cout << colors[(unsigned)bl[0]] << colors[(unsigned)bl[1]]
         << ' ' << (unsigned)this->getCubieIndex(bl) << endl;

    // BR YG 7.
    edge_t br =
    {
      cube.get(F::BACK,  1, 0),
      cube.get(F::RIGHT, 1, 2)
    };

    cout << colors[(unsigned)br[0]] << colors[(unsigned)br[1]]
         << ' ' << (unsigned)this->getCubieIndex(br) << endl;

    // DF OW 8.
    edge_t df =
    {
      cube.get(F::DOWN,  0, 1),
      cube.get(F::FRONT, 2, 1)
    };

    cout << colors[(unsigned)df[0]] << colors[(unsigned)df[1]]
         << ' ' << (unsigned)this->getCubieIndex(df) << endl;

    // DL OB 9.
    edge_t dl =
    {
      cube.get(F::DOWN, 1, 0),
      cube.get(F::LEFT, 2, 1)
    };

    cout << colors[(unsigned)dl[0]] << colors[(unsigned)dl[1]]
         << ' ' << (unsigned)this->getCubieIndex(dl) << endl;

    // DB OY 10.
    edge_t db =
    {
      cube.get(F::DOWN, 2, 1),
      cube.get(F::BACK, 2, 1)
    };

    cout << colors[(unsigned)db[0]] << colors[(unsigned)db[1]]
         << ' ' << (unsigned)this->getCubieIndex(db) << endl;

    // DR OG 11.
    edge_t dr =
    {
      cube.get(F::DOWN,  1, 2),
      cube.get(F::RIGHT, 2, 1)
    };

    cout << colors[(unsigned)dr[0]] << colors[(unsigned)dr[1]]
         << ' ' << (unsigned)this->getCubieIndex(dr) << endl;

    perm_t edgePerm =
    {
      this->getCubieIndex(bl),
      this->getCubieIndex(br),
      this->getCubieIndex(df),
      this->getCubieIndex(dl),
      this->getCubieIndex(db),
      this->getCubieIndex(dr)
    };

    for (unsigned i: edgePerm)
      cout << i << ' ';
    cout << endl;

    // Now get the orientation of each edge.
    array<uchar, 6> edgeOrientations =
    {
      this->getCubieOrientation(bl),
      this->getCubieOrientation(br),
      this->getCubieOrientation(df),
      this->getCubieOrientation(dl),
      this->getCubieOrientation(db),
      this->getCubieOrientation(dr)
    };

    for (unsigned i: edgeOrientations)
      cout << i << ' ';
    cout << endl;

    return EdgePatternDatabase::getDatabaseIndex(edgePerm, edgeOrientations);
  }
}

