#include "Scrambler.h"

namespace busybin
{
  /**
   * Init.  All params must remain in scope.
   * @param cube A RubiksCube.
   * @param mStore The move store, used for scrambling the cube.
   * @param cubeView A RubiksCubeView.
   */
  Scrambler::Scrambler(const RubiksCube& rCube, MoveStore& mStore,
    const RubiksCubeView& cubeView) : 
    cube(&rCube), moveStore(&mStore), view(&cubeView)
  {
  }

  /**
   * Let the user scramble the cube.
   */
  void Scrambler::manualScramble()
  {
    bool done = false;

    while (!done)
    {
      string         input;
      string         move;
      istringstream  splitter;
      vector<string> moves;
      bool           validMoves;

      // Display the cube.
      this->view->render(*this->cube);

      // Get a move.
      cin.clear();
      cout << "Enter a move.  When done enter \"Q\": ";
      getline(cin, input);

      // Quit.
      if (input == "Q")
        return;

      // Split the string.
      if (input != "")
      {
        validMoves = true;
        moves.clear();
        splitter.clear();
        splitter.str(input);

        while (splitter >> move && validMoves)
        {
          if (this->moveStore->isValidMove(move))
            moves.push_back(move);
          else
            validMoves = false;
        }

        if (validMoves)
        {
          // Apply the move.
          for (const string& move : moves)
          {
            cout << move << ' ';
            this->moveStore->getMoveFunc(move)();
          }
          cout << endl;
        }
      }
    }
  }
}

