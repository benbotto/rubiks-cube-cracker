#ifndef _BUSYBIN_KORF_CUBE_SOLVER_H_
#define _BUSYBIN_KORF_CUBE_SOLVER_H_

#include "CubeSolver.h"
#include "../CubeMover.h"
#include "../../../View/RubiksCubeView.h"
#include "../../../Model/RubiksCubeModel.h"
#include "../../../Model/RubiksCubeIndexModel.h"
#include "../../../Model/Goal/Goal.h"
#include "../../../Model/Goal/OrientGoal.h"
#include "../../../Model/Goal/SolveGoal.h"
#include "../../../Model/Goal/Korf/CornerDatabaseGoal.h"
#include "../../../Model/Goal/Korf/EdgeDatabaseGoal.h"
#include "../../../Model/Goal/Korf/EdgePermutationDatabaseGoal.h"
#include "../../../Model/MoveStore/TwistStore.h"
#include "../../../Model/MoveStore/RotationStore.h"
#include "../../../OpenGLSeed/Model/World.h"
#include "../../../OpenGLSeed/View/WorldWindow.h"
#include "../../../Model/PatternDatabase/Korf/CornerPatternDatabase.h"
#include "../../../Model/PatternDatabase/Korf/EdgeG1PatternDatabase.h"
#include "../../../Model/PatternDatabase/Korf/EdgeG2PatternDatabase.h"
#include "../../../Model/PatternDatabase/Korf/EdgePermutationPatternDatabase.h"
#include "../../../Model/PatternDatabase/Korf/KorfPatternDatabase.h"
#include "../../../Util/ThreadPool.h"
#include "../../Searcher/BreadthFirstCubeSearcher.h"
#include "../../Searcher/PatternDatabaseIndexer.h"
#include "../../Searcher/IDACubeSearcher.h"
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
#include <memory>
using std::unique_ptr;
#include <atomic>
using std::atomic_bool;

namespace busybin
{
  /**
   * Solver controller for the cube.  Solves using the Korf method.
   */
  class KorfCubeSolver : public CubeSolver
  {
    CornerPatternDatabase          cornerDB;
    EdgeG1PatternDatabase          edgeG1DB;
    EdgeG2PatternDatabase          edgeG2DB;
    EdgePermutationPatternDatabase edgePermDB;
    KorfPatternDatabase            korfDB;

    atomic_bool cornerDBIndexed;
    atomic_bool edgeG1DBIndexed;
    atomic_bool edgeG2DBIndexed;
    atomic_bool edgePermDBIndexed;

    void indexCornerDatabase();
    void indexEdgeG1Database();
    void indexEdgeG2Database();
    void indexEdgePermDatabase();
    void onIndexComplete();

  protected:
    void solveCube();

  public:
    KorfCubeSolver(World* pWorld, WorldWindow* pWorldWnd,
      CubeMover* pMover, ThreadPool* pThreadPool);
    void initialize();
  };
}

#endif

