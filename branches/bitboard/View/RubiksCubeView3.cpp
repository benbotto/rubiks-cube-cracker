#include "RubiksCubeView3.h"

namespace busybin
{
  /**
   * Render the cube.
   * @param cube The RubiksCube.
   */
  void RubiksCubeView3::render(const RubiksCubeModel3& cube) const
  {
    char colors[] = {'W', 'G', 'R', 'B', 'O', 'Y'};

    cout << setfill(' ') << '\n';

    // Up face.
    for (unsigned row = 0; row < 3; ++ row)
    {
      cout << setw(8) << right;

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(RubiksCubeModel3::FACE::UP, row, col)] << ' ';
      cout << '\n';
    }
    cout << endl;


    // Left front, right, back.
    for (unsigned row = 0; row < 3; ++ row)
    {
      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(RubiksCubeModel3::FACE::LEFT,  row, col)] << ' ';
      cout << ' ';

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(RubiksCubeModel3::FACE::FRONT, row, col)] << ' ';
      cout << ' ';

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(RubiksCubeModel3::FACE::RIGHT, row, col)] << ' ';
      cout << ' ';

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(RubiksCubeModel3::FACE::BACK,  row, col)] << ' ';
      cout << '\n';
    }
    cout << endl;

    // Down face.
    for (unsigned row = 0; row < 3; ++ row)
    {
      cout << setw(8) << right;

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(RubiksCubeModel3::FACE::DOWN, row, col)] << ' ';
      cout << '\n';
    }

    cout << endl;
  }
}

