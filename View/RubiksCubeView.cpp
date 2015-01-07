#include "RubiksCubeView.h"

namespace busybin
{
  /**
   * Render the cube.
   * @param cube The RubiksCube.
   */
  void RubiksCubeView::render(const RubiksCubeModel& cube) const
  {
    cout << '\n';

    // Up face.
    for (unsigned row = 0; row < 3; ++ row)
    {
      cout << setw(8) << right;

      for (unsigned col = 0; col < 3; ++ col)
        cout << (char)cube.get(RubiksCubeModel::FACE::UP, row, col) << ' ';
      cout << '\n';
    }
    cout << endl;


    // Left front, right, back.
    for (unsigned row = 0; row < 3; ++ row)
    {
      for (unsigned col = 0; col < 3; ++ col)
        cout << (char)cube.get(RubiksCubeModel::FACE::LEFT,  row, col) << ' ';
      cout << ' ';

      for (unsigned col = 0; col < 3; ++ col)
        cout << (char)cube.get(RubiksCubeModel::FACE::FRONT, row, col) << ' ';
      cout << ' ';

      for (unsigned col = 0; col < 3; ++ col)
        cout << (char)cube.get(RubiksCubeModel::FACE::RIGHT, row, col) << ' ';
      cout << ' ';

      for (unsigned col = 0; col < 3; ++ col)
        cout << (char)cube.get(RubiksCubeModel::FACE::BACK,  row, col) << ' ';
      cout << '\n';
    }
    cout << endl;

    // Down face.
    for (unsigned row = 0; row < 3; ++ row)
    {
      cout << setw(8) << right;

      for (unsigned col = 0; col < 3; ++ col)
        cout << (char)cube.get(RubiksCubeModel::FACE::DOWN, row, col) << ' ';
      cout << '\n';
    }

    cout << endl;
  }
}

