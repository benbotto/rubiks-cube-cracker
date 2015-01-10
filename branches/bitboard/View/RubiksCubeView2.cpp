#include "RubiksCubeView2.h"

namespace busybin
{
  /**
   * Render the cube.
   * @param cube The RubiksCube.
   */
  void RubiksCubeView2::renderRaw(const RubiksCubeModel2& cube) const
  {
    cout << "\nFACE   HEX        7   6   5   4   3   2   1   0\n"
         << "--------------------------------------------------";

    cout << '\n' << left << setw(7) << setfill(' ') << "UP";
    printFaceRaw(cube.getFace(RubiksCubeModel2::FACE::UP));
    cout << '\n' << left << setw(7) << setfill(' ') << "LEFT";
    printFaceRaw(cube.getFace(RubiksCubeModel2::FACE::LEFT));
    cout << '\n' << left << setw(7) << setfill(' ') << "FRONT";
    printFaceRaw(cube.getFace(RubiksCubeModel2::FACE::FRONT));
    cout << '\n' << left << setw(7) << setfill(' ') << "RIGHT";
    printFaceRaw(cube.getFace(RubiksCubeModel2::FACE::RIGHT));
    cout << '\n' << left << setw(7) << setfill(' ') << "BACK";
    printFaceRaw(cube.getFace(RubiksCubeModel2::FACE::BACK));
    cout << '\n' << left << setw(7) << setfill(' ') << "DOWN";
    printFaceRaw(cube.getFace(RubiksCubeModel2::FACE::DOWN));

    // Reset io flags.
    cout << setfill(' ') << dec;

    cout << '\n' << endl;
  }

  /**
   * Render a sing flace.
   * @param f The face.
   */
  void RubiksCubeView2::printFaceRaw(unsigned face) const
  {
    bitset<24> bFace = face;

    cout << "0x" << setw(7) << hex << setfill('0') << left << face
         << "  ";

    for (int i = 23; i >= 0; --i)
    {
      if (i != 23 && ((i + 1) % 3) == 0)
        cout << ' ';
      cout << bFace[i];
    }
  }

  /**
   * Render the cube.
   * @param cube The RubiksCube.
   */
  void RubiksCubeView2::render(const RubiksCubeModel2& cube) const
  {
    char colors[] = {'W', 'G', 'R', 'B', 'O', 'Y'};

    cout << '\n';

    // Up face.
    for (unsigned row = 0; row < 3; ++ row)
    {
      cout << setw(8) << right;

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(RubiksCubeModel2::FACE::UP, row, col)] << ' ';
      cout << '\n';
    }
    cout << endl;


    // Left front, right, back.
    for (unsigned row = 0; row < 3; ++ row)
    {
      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(RubiksCubeModel2::FACE::LEFT,  row, col)] << ' ';
      cout << ' ';

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(RubiksCubeModel2::FACE::FRONT, row, col)] << ' ';
      cout << ' ';

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(RubiksCubeModel2::FACE::RIGHT, row, col)] << ' ';
      cout << ' ';

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(RubiksCubeModel2::FACE::BACK,  row, col)] << ' ';
      cout << '\n';
    }
    cout << endl;

    // Down face.
    for (unsigned row = 0; row < 3; ++ row)
    {
      cout << setw(8) << right;

      for (unsigned col = 0; col < 3; ++ col)
        cout << colors[(unsigned)cube.get(RubiksCubeModel2::FACE::DOWN, row, col)] << ' ';
      cout << '\n';
    }

    cout << endl;
  }
}

