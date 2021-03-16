#ifndef _BUSYBIN_THISTLETHWAITE_CUBE_SOLVER_H_
#define _BUSYBIN_THISTLETHWAITE_CUBE_SOLVER_H_

#include "CubeSolver.h"
#include "../CubeMover.h"
#include "../../Searcher/IDACubeSearcher.h"
#include "../../Searcher/BreadthFirstCubeSearcher.h"
#include "../../Searcher/PatternDatabaseIndexer.h"
#include "../../../View/RubiksCubeView.h"
#include "../../../Model/RubiksCubeModel.h"
#include "../../../Model/MoveStore/TwistStore.h"
#include "../../../Model/MoveStore/G1TwistStore.h"
#include "../../../Model/MoveStore/G2TwistStore.h"
#include "../../../Model/MoveStore/G3TwistStore.h"
#include "../../../Model/MoveStore/RotationStore.h"
#include "../../../Model/Goal/Goal.h"
#include "../../../Model/Goal/OrientGoal.h"
#include "../../../Model/Goal/Thistlethwaite/G1DatabaseGoal.h"
#include "../../../Model/Goal/Thistlethwaite/G2DatabaseGoal.h"
#include "../../../Model/Goal/Thistlethwaite/G3DatabaseGoal.h"
#include "../../../Model/Goal/Thistlethwaite/G4DatabaseGoal.h"
#include "../../../Model/Goal/Thistlethwaite/GoalG0_G1.h"
#include "../../../Model/Goal/Thistlethwaite/GoalG1_G2.h"
#include "../../../Model/Goal/Thistlethwaite/GoalG2_G3.h"
#include "../../../Model/Goal/Thistlethwaite/GoalG3_G4.h"
#include "../../../Model/Goal/SolveGoal.h"
#include "../../../Model/PatternDatabase/Thistlethwaite/G1PatternDatabase.h"
#include "../../../Model/PatternDatabase/Thistlethwaite/G2PatternDatabase.h"
#include "../../../OpenGLSeed/Model/World.h"
#include "../../../OpenGLSeed/View/WorldWindow.h"
#include "../../../Util/ThreadPool.h"
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;

namespace busybin
{
  /**
   * Solver controller for the cube.  Solves using the Thistlethwaite method.
   */
  class ThistlethwaiteCubeSolver : public CubeSolver
  {
    G1PatternDatabase g1DB;
    G2PatternDatabase g2DB;
    G3PatternDatabase g3DB;
    G4PatternDatabase g4DB;

    void indexG1Database();
    void indexG2Database();
    void indexG3Database();
    void indexG4Database();

  protected:
    void solveCube();

  public:
    ThistlethwaiteCubeSolver(World* pWorld, WorldWindow* pWorldWnd,
      CubeMover* pMover, ThreadPool* pThreadPool);
    void initialize();
  };
}

#endif
