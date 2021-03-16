cmake_minimum_required(VERSION 2.6)
project(RubiksCube)

# All source files.
set(SRC
  "./rubiksCube.cpp"
  "./Controller/Command/CubeMover.cpp"
  "./Controller/Command/CubeDumper.cpp"
  "./Controller/Command/CubeScrambler.cpp"
  "./Controller/Command/Solver/CubeSolver.cpp"
  "./Controller/Command/Solver/ThistlethwaiteCubeSolver.cpp"
  "./Controller/Command/Solver/KorfCubeSolver.cpp"
  "./Controller/RubiksCubeController.cpp"
  "./Controller/GL/Program/RubiksCubeProgram.cpp"
  "./Controller/Searcher/MovePruner.cpp"
  "./Controller/Searcher/CubeSearcher.cpp"
  "./Controller/Searcher/IDDFSCubeSearcher.cpp"
  "./Controller/Searcher/IDACubeSearcher.cpp"
  "./Controller/Searcher/BreadthFirstCubeSearcher.cpp"
  "./Controller/Searcher/PatternDatabaseIndexer.cpp"
  "./View/RubiksCubeView.cpp"
  "./Util/math.cpp"
  "./Util/RubiksCubeException.cpp"
  "./Util/Random.cpp"
  "./Util/Timer.cpp"
  "./Util/AutoTimer.cpp"
  "./Util/ThreadPool.cpp"
  "./Util/NibbleArray.cpp"
  "./Model/MoveStore/MoveStore.cpp"
  "./Model/MoveStore/RotationStore.cpp"
  "./Model/MoveStore/TwistStore.cpp"
  "./Model/MoveStore/G1TwistStore.cpp"
  "./Model/MoveStore/G2TwistStore.cpp"
  "./Model/MoveStore/G3TwistStore.cpp"
  "./Model/PatternDatabase/PatternDatabase.cpp"
  "./Model/PatternDatabase/Korf/CornerPatternDatabase.cpp"
  "./Model/PatternDatabase/Korf/EdgePatternDatabase.cpp"
  "./Model/PatternDatabase/Korf/EdgeG1PatternDatabase.cpp"
  "./Model/PatternDatabase/Korf/EdgeG2PatternDatabase.cpp"
  "./Model/PatternDatabase/Korf/EdgePermutationPatternDatabase.cpp"
  "./Model/PatternDatabase/Korf/KorfPatternDatabase.cpp"
  "./Model/PatternDatabase/Thistlethwaite/G1PatternDatabase.cpp"
  "./Model/PatternDatabase/Thistlethwaite/G2PatternDatabase.cpp"
  "./Model/PatternDatabase/Thistlethwaite/G3PatternDatabase.cpp"
  "./Model/PatternDatabase/Thistlethwaite/G4PatternDatabase.cpp"
  "./Model/PatternDatabase/TestPatternDatabase.cpp"
  "./Model/RubiksCubeWorld.cpp"
  "./Model/RubiksCube.cpp"
  "./Model/RubiksCubeModel.cpp"
  "./Model/RubiksCubeIndexModel.cpp"
  "./Model/Goal/Goal.cpp"
  "./Model/Goal/OrientGoal.cpp"
  "./Model/Goal/SolveGoal.cpp"
  "./Model/Goal/TestGoal.cpp"
  "./Model/Goal/DatabaseGoal.cpp"
  "./Model/Goal/Thistlethwaite/G1DatabaseGoal.cpp"
  "./Model/Goal/Thistlethwaite/G2DatabaseGoal.cpp"
  "./Model/Goal/Thistlethwaite/G3DatabaseGoal.cpp"
  "./Model/Goal/Thistlethwaite/G4DatabaseGoal.cpp"
  "./Model/Goal/Thistlethwaite/GoalG0_G1.cpp"
  "./Model/Goal/Thistlethwaite/GoalG1_G2.cpp"
  "./Model/Goal/Thistlethwaite/GoalG2_G3.cpp"
  "./Model/Goal/Thistlethwaite/GoalG3_G4.cpp"
  "./Model/Goal/Korf/CornerDatabaseGoal.cpp"
  "./Model/Goal/Korf/EdgeDatabaseGoal.cpp"
  "./Model/Goal/Korf/EdgePermutationDatabaseGoal.cpp"
  "./Model/WorldObject/Cubie.cpp"
  "./Model/WorldObject/RubiksCubeWorldObject.cpp")

# Build the RubiksCube executable.
add_executable(rubiksCube ${SRC})

# Release build by default.
IF(NOT CMAKE_BUILD_TYPE )
  set(CMAKE_BUILD_TYPE Release)
ENDIF(NOT CMAKE_BUILD_TYPE)

# Link the OpenGLSeed library.
set (OpenGL_GL_PREFERENCE "GLVND")
add_subdirectory(OpenGLSeed)
target_link_libraries(rubiksCube OpenGLSeed)

# TODO: Make cross platform.
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -Wall -pedantic -std=c++0x -Wno-strict-aliasing -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -march=native -ffast-math -finline-functions -funroll-all-loops -flto")
set(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

# The Find*.cmake files are here.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/OpenGLSeed/cmake/modules/")

# GLM.
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

# GLEW.
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(rubiksCube ${GLEW_LIBRARIES})

# GLFW.
find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(rubiksCube ${GLFW_LIBRARIES})

# OpenGL.
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(rubiksCube ${OPENGL_LIBRARIES})

