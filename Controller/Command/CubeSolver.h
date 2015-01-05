#ifndef _BUSYBIN_CUBE_SOLVER_H_
#define _BUSYBIN_CUBE_SOLVER_H_

#include "CubeMover.h"
#include "../CubeSearcher.h"
#include "../../View/RubiksCubeView.h"
#include "../../Util/ThreadPool.h"
#include "../../Util/Timer.h"
#include "../../Model/WorldObject/RubiksCube.h"
#include "../../Model/RubiksCubeModel.h"
#include "../../Model/MoveStore/ModelTwistStore.h"
#include "../../Model/MoveStore/ModelRotationStore.h"
#include "../../Model/MoveStore/CubeTwistStore.h"
#include "../../Model/MoveStore/CubeRotationStore.h"
#include "../../Model/Goal/Goal.h"
#include "../../Model/Goal/Goal2x2x2.h"
#include "../../Model/Goal/Orient2x2x2.h"
#include "../../Model/Goal/Goal2x2x2_1x1x2.h"
#include "../../Model/Goal/Orient2x2x2_1x1x2.h"
#include "../../Model/Goal/Goal2x2x3.h"
#include "../../Model/Goal/Orient2x2x3.h"
#include "../../Model/Goal/Goal2x2x3_1x1x2.h"
#include "../../Model/Goal/Orient2x2x3_1x1x2.h"
#include "../../Model/Goal/Goal2x2x3_1x2x2.h"
#include "../../Model/Goal/Orient2x2x3_1x2x2.h"
#include "../../Model/Goal/Goal2x2x3_1x2x2_1x1x2.h"
#include "../../Model/Goal/Goal2x3x3.h"
#include "../../Model/Goal/Goal2x3x3_OE.h"
#include "../../Model/Goal/Goal3x3x3.h"
#include "../../OpenGLSeed/Controller/Command/Command.h"
#include "../../OpenGLSeed/Model/World.h"
#include "../../OpenGLSeed/View/WorldWindow.h"
#include <iostream>
using std::cout;
using std::endl;
#include <functional>
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;
#include <atomic>
using std::atomic_bool;
#include <mutex>
using std::mutex;
using std::lock_guard;
#include <vector>
using std::vector;
#include <queue>
using std::queue;
#include <memory>
using std::unique_ptr;
#include <utility>
using std::pair;

namespace busybin
{
  /**
   * Solver controller for the cube.
   */
  class CubeSolver : public Command
  {
    struct GoalAndMoveStore
    {
      unique_ptr<Goal> pGoal;
      MoveStore*       pMoveStore;
    };

    ThreadPool        threadPool;
    RubiksCube*       pCube;
    RubiksCubeModel   cubeModel;
    CubeTwistStore    cubeTwistStore;
    CubeRotationStore cubeRotStore;
    CubeMover*        pMover;
    atomic_bool       solving;
    atomic_bool       movesInQueue;
    queue<string>     moveQueue;
    mutex             moveMutex;
    Timer             moveTimer;

    void solveCube();
    void processGoalMoves(const Goal& goal, MoveStore& moveStore,
      unsigned goalNum, vector<string>& allMoves, vector<string>& goalMoves);

  public:
    CubeSolver(World* pWorld, WorldWindow* pWorldWnd, CubeMover* pMover);
    void onKeypress(int key, int scancode, int action, int mods);
    void onPulse(double elapsed);
  };
}

#endif
