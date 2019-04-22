#ifndef _BUSYBIN_KORF_CUBE_SOLVER_H_
#define _BUSYBIN_KORF_CUBE_SOLVER_H_

#include "CubeSolver.h"
#include "../CubeMover.h"
#include "../../../View/RubiksCubeView.h"
#include "../../../Model/RubiksCubeModel.h"
#include "../../../Model/Goal/Goal.h"
#include "../../../Model/MoveStore/ModelTwistStore.h"
#include "../../../OpenGLSeed/Model/World.h"
#include "../../../OpenGLSeed/View/WorldWindow.h"
#include "../../../Model/Goal/Korf/GoalG1_CornerDatabase.h"
#include "../../../Model/PatternDatabase/PatternDatabase.h"
#include "../../../Model/PatternDatabase/CornerPatternDatabase.h"
#include "../../Searcher/BreadthFirstCubeSearcher.h"
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
   * Solver controller for the cube.  Solves using the Korf method.
   */
  class KorfCubeSolver : public CubeSolver
  {
    CornerPatternDatabase cornerDB;

    void indexDatabases();

  protected:
    void solveCube();

  public:
    KorfCubeSolver(World* pWorld, WorldWindow* pWorldWnd, CubeMover* pMover);
    void initialize();
  };
}

#endif

