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
#include "../../../Model/Goal/Korf/CornerDatabaseGoal.h"
#include "../../../Model/Goal/Korf/EdgeDatabaseGoal.h"
#include "../../../Model/PatternDatabase/Korf/CornerPatternDatabase.h"
#include "../../../Model/PatternDatabase/Korf/EdgeG1PatternDatabase.h"
#include "../../../Model/PatternDatabase/Korf/EdgeG2PatternDatabase.h"
#include "../../../Util/ThreadPool.h"
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
    EdgeG1PatternDatabase edgeG1DB;
    EdgeG2PatternDatabase edgeG2DB;

    void indexDatabases();

  protected:
    void solveCube();

  public:
    KorfCubeSolver(World* pWorld, WorldWindow* pWorldWnd,
      CubeMover* pMover, ThreadPool* pThreadPool);
    void initialize();
  };
}

#endif

