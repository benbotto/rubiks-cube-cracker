#include "RubiksCubeController.h"

namespace busybin
{
  /**
   * Initialize.
   */
  RubiksCubeController::RubiksCubeController()
  {
    // Set up the move map.
    this->moveMap["L"]  = bind(&RubiksCube::l,      &this->cube);
    this->moveMap["L'"] = bind(&RubiksCube::lPrime, &this->cube);
    this->moveMap["L2"] = bind(&RubiksCube::l2,     &this->cube);

    this->moveMap["R"]  = bind(&RubiksCube::r,      &this->cube);
    this->moveMap["R'"] = bind(&RubiksCube::rPrime, &this->cube);
    this->moveMap["R2"] = bind(&RubiksCube::r2,     &this->cube);

    this->moveMap["U"]  = bind(&RubiksCube::u,      &this->cube);
    this->moveMap["U'"] = bind(&RubiksCube::uPrime, &this->cube);
    this->moveMap["U2"] = bind(&RubiksCube::u2,     &this->cube);

    this->moveMap["D"]  = bind(&RubiksCube::d,      &this->cube);
    this->moveMap["D'"] = bind(&RubiksCube::dPrime, &this->cube);
    this->moveMap["D2"] = bind(&RubiksCube::d2,     &this->cube);

    this->moveMap["F"]  = bind(&RubiksCube::f,      &this->cube);
    this->moveMap["F'"] = bind(&RubiksCube::fPrime, &this->cube);
    this->moveMap["F2"] = bind(&RubiksCube::f2,     &this->cube);

    this->moveMap["B"]  = bind(&RubiksCube::b,      &this->cube);
    this->moveMap["B'"] = bind(&RubiksCube::bPrime, &this->cube);
    this->moveMap["B2"] = bind(&RubiksCube::b2,     &this->cube);
  }

  /**
   * Main game loop.
   */
  void RubiksCubeController::start()
  {
    ChromosomeGenerator chromGen;

    // Let the user scramble the cube.
    this->manualScramble();

    cout << this->evaluator.eval(this->cube) << endl;
    
    // Generate a bunch of random moves, or "chromosomes."
    /*vector<string> c = chromGen.generateChromosome(30);

    for (const string& move : c)
      cout << move << ' ';
    cout << endl;

    c = chromGen.generateChromosome(30);

    for (const string& move : c)
      cout << move << ' ';
    cout << endl;

    c = chromGen.generateChromosome(30);

    for (const string& move : c)
      cout << move << ' ';
    cout << endl;*/
  }

  /**
   * Let the user scramble the cube.
   */
  void RubiksCubeController::manualScramble()
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
      this->view.render(this->cube);

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
          if (this->moveMap.count(move))
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
            this->moveMap[move]();
          }
          cout << endl;
        }
      }
    }
  }

  /**
   * Generate chromosomes.
   */
  void generateChromosomes()
  {

  }
}

