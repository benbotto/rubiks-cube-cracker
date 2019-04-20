#ifndef _BUSYBIN_THISTLETHWAITE_CUBE_SOLVER_H_
#define _BUSYBIN_THISTLETHWAITE_CUBE_SOLVER_H_

#include "CubeSolver.h"
#include "CubeMover.h"
#include "../Searcher/IDDFSCubeSearcher.h"
#include "../../View/RubiksCubeView.h"
#include "../../Model/RubiksCubeModel.h"
#include "../../Model/MoveStore/ModelTwistStore.h"
#include "../../Model/MoveStore/ModelG1TwistStore.h"
#include "../../Model/MoveStore/ModelG2TwistStore.h"
#include "../../Model/MoveStore/ModelG3TwistStore.h"
#include "../../Model/MoveStore/ModelRotationStore.h"
#include "../../Model/Goal/Goal.h"
#include "../../Model/Goal/OrientG0.h"
#include "../../Model/Goal/Thistlethwaite/GoalG0_G1.h"
#include "../../Model/Goal/Thistlethwaite/GoalG1_G2.h"
#include "../../Model/Goal/Thistlethwaite/GoalG2_G3_Corners.h"
#include "../../Model/Goal/Thistlethwaite/GoalG2_G3_Edges.h"
#include "../../Model/Goal/Thistlethwaite/GoalG3_Permute_Corners.h"
#include "../../Model/Goal/GoalG3_Solved.h"
#include "../../OpenGLSeed/Model/World.h"
#include "../../OpenGLSeed/View/WorldWindow.h"
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <memory>
using std::unique_ptr;
#include <string>
using std::string;
#include <sstream>
using std::istringstream;
#include <iterator>
using std::istream_iterator;

namespace busybin
{
  /**
   * Solver controller for the cube.  Solves using the Thistlethwaite method.
   */
  class ThistlethwaiteCubeSolver : public CubeSolver
  {
    struct GoalAndMoveStore
    {
      unique_ptr<Goal> pGoal;
      MoveStore*       pMoveStore;
    };

    GoalG3_Permute_Corners g3Perms;
    IDDFSCubeSearcher      searcher;

  protected:
    void solveCube();

  public:
    ThistlethwaiteCubeSolver(World* pWorld, WorldWindow* pWorldWnd, CubeMover* pMover);
  };
}

#endif

