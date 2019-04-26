cmake_minimum_required(VERSION 2.6)
project(RubiksCube)

# All source files.
set(SRC
  "./rubiksCube.cpp"
  "./Controller/Command/CubeMover.cpp"
  "./Controller/Command/CubeDumper.cpp"
  "./Controller/Command/Solver/CubeSolver.cpp"
  "./Controller/Command/Solver/ThistlethwaiteCubeSolver.cpp"
  "./Controller/Command/Solver/KorfCubeSolver.cpp"
  "./Controller/RubiksCubeController.cpp"
  "./Controller/GL/Program/RubiksCubeProgram.cpp"
  "./Controller/Searcher/CubeSearcher.cpp"
  "./Controller/Searcher/IDDFSCubeSearcher.cpp"
  "./Controller/Searcher/IDACubeSearcher.cpp"
  "./Controller/Searcher/BreadthFirstCubeSearcher.cpp"
  "./View/RubiksCubeView.cpp"
  "./Util/RubiksCubeException.cpp"
  "./Util/Random.cpp"
  "./Util/Timer.cpp"
  "./Util/AutoTimer.cpp"
  "./Util/ThreadPool.cpp"
  "./Util/NibbleArray.cpp"
  "./Model/MoveStore/MoveStore.cpp"
  "./Model/MoveStore/RotationStore.cpp"
  "./Model/MoveStore/TwistStore.cpp"
  "./Model/MoveStore/CubeRotationStore.cpp"
  "./Model/MoveStore/CubeTwistStore.cpp"
  "./Model/MoveStore/ModelRotationStore.cpp"
  "./Model/MoveStore/ModelTwistStore.cpp"
  "./Model/MoveStore/ModelG1TwistStore.cpp"
  "./Model/MoveStore/ModelG2TwistStore.cpp"
  "./Model/MoveStore/ModelG3TwistStore.cpp"
  "./Model/PatternDatabase/PatternDatabase.cpp"
  "./Model/PatternDatabase/Korf/CornerPatternDatabase.cpp"
  "./Model/PatternDatabase/Korf/EdgePatternDatabase.cpp"
  "./Model/PatternDatabase/Korf/EdgeG1PatternDatabase.cpp"
  "./Model/PatternDatabase/Korf/EdgeG2PatternDatabase.cpp"
  "./Model/PatternDatabase/Korf/KorfPatternDatabase.cpp"
  "./Model/RubiksCubeWorld.cpp"
  "./Model/RubiksCubeModel.cpp"
  "./Model/Goal/Goal.cpp"
  "./Model/Goal/OrientGoal.cpp"
  "./Model/Goal/SolveGoal.cpp"
  "./Model/Goal/TestGoal.cpp"
  "./Model/Goal/DatabaseGoal.cpp"
  "./Model/Goal/Thistlethwaite/GoalG0_G1.cpp"
  "./Model/Goal/Thistlethwaite/GoalG1_G2.cpp"
  "./Model/Goal/Thistlethwaite/GoalG2_G3_Corners.cpp"
  "./Model/Goal/Thistlethwaite/GoalG2_G3_Edges.cpp"
  "./Model/Goal/Thistlethwaite/GoalG3_Permute_Corners.cpp"
  "./Model/Goal/Korf/CornerDatabaseGoal.cpp"
  "./Model/Goal/Korf/EdgeDatabaseGoal.cpp"
  "./Model/WorldObject/Cubie.cpp"
  "./Model/WorldObject/RubiksCube.cpp")

# Build the RubiksCubee executable.
add_executable(rubiksCube ${SRC})

# Release build by default.
set(CMAKE_BUILD_TYPE Release)

# Link the OpenGLSeed library.
add_subdirectory(OpenGLSeed)
target_link_libraries(rubiksCube OpenGLSeed)

# TODO: Make cross platform.
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -Wall -pedantic -std=c++0x -Wno-strict-aliasing -pthread")

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
target_link_libraries(rubiksCube ${OPENGL_gl_LIBRARY})

