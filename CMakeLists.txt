cmake_minimum_required(VERSION 2.6)
project(RubiksCube)

# All source files.
set(SRC
  "./rubiksCube.cpp"
  "./Controller/Command/CubeMover.cpp"
  "./Controller/Command/CubeSolver.cpp"
  "./Controller/Command/ThistlethwaiteCubeSolver.cpp"
  "./Controller/Command/CubeDumper.cpp"
  "./Controller/RubiksCubeController.cpp"
  "./Controller/GL/Program/RubiksCubeProgram.cpp"
  "./Controller/CubeSearcher.cpp"
  "./Controller/IDDFSCubeSearcher.cpp"
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
  "./Model/PatternDatabase/CornerPatternDatabase.cpp"
  "./Model/PatternDatabase/EdgePatternDatabase.cpp"
  "./Model/PatternDatabase/EdgeG1PatternDatabase.cpp"
  "./Model/PatternDatabase/EdgeG2PatternDatabase.cpp"
  "./Model/RubiksCubeWorld.cpp"
  "./Model/RubiksCubeModel.cpp"
  "./Model/Goal/OrientG0.cpp"
  "./Model/Goal/GoalG0_G1.cpp"
  "./Model/Goal/GoalG1_G2.cpp"
  "./Model/Goal/GoalG2_G3_Corners.cpp"
  "./Model/Goal/GoalG2_G3_Edges.cpp"
  "./Model/Goal/GoalG3_Solved.cpp"
  "./Model/Goal/GoalG3_Permute_Corners.cpp"
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

