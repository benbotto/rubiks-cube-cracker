#include "RubiksCubeView.h"

namespace busybin
{
  /**
   * Render the cube.
   * @param cube The RubiksCube.
   */
  void RubiksCubeView::render(const RubiksCubeModel& cube) const
  {
    typedef RubiksCubeModel::FACE F;

    char colors[] = {'W', 'G', 'R', 'B', 'O', 'Y'};

    cout << setfill(' ') << '\n';

    // Up face.
    for (unsigned row = 0; row < 3; ++ row)
    {
      cout << setw(8) << right;

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(F::UP, row, col)] << ' ';
      cout << '\n';
    }
    cout << endl;


    // Left front, right, back.
    for (unsigned row = 0; row < 3; ++ row)
    {
      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(F::LEFT,  row, col)] << ' ';
      cout << ' ';

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(F::FRONT, row, col)] << ' ';
      cout << ' ';

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(F::RIGHT, row, col)] << ' ';
      cout << ' ';

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(F::BACK,  row, col)] << ' ';
      cout << '\n';
    }
    cout << endl;

    // Down face.
    for (unsigned row = 0; row < 3; ++ row)
    {
      cout << setw(8) << right;

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(F::DOWN, row, col)] << ' ';
      cout << '\n';
    }

    cout << endl;
  }
}

