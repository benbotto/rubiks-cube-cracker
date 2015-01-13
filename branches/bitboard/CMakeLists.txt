cmake_minimum_required (VERSION 2.6)
project (RubiksCube)

# All source files.
set (SRC
  "./rubiksCube.cpp"
  "./Controller/Command/CubeMover.cpp"
  "./Controller/Command/CubeSolver.cpp"
  "./Controller/RubiksCubeController.cpp"
  "./Controller/GL/Program/RubiksCubeProgram.cpp"
  "./Controller/CubeSearcher.cpp"
  "./View/RubiksCubeView.cpp"
  "./Util/RubiksCubeException.cpp"
  "./Util/Random.cpp"
  "./Util/Timer.cpp"
  "./Util/AutoTimer.cpp"
  "./Util/ThreadPool.cpp"
  "./Model/MoveStore/MoveStore.cpp"
  "./Model/MoveStore/RotationStore.cpp"
  "./Model/MoveStore/TwistStore.cpp"
  "./Model/MoveStore/CubeRotationStore.cpp"
  "./Model/MoveStore/CubeTwistStore.cpp"
  "./Model/MoveStore/ModelRotationStore.cpp"
  "./Model/MoveStore/ModelTwistStore.cpp"
  "./Model/RubiksCubeWorld.cpp"
  "./Model/Goal/Goal.cpp"
  "./Model/Goal/Goal2x2x2.cpp"
  "./Model/Goal/Orient2x2x2.cpp"
  "./Model/Goal/Goal2x2x2_1x1x2.cpp"
  "./Model/Goal/Orient2x2x2_1x1x2.cpp"
  "./Model/Goal/Goal2x2x3.cpp"
  "./Model/Goal/Orient2x2x3.cpp"
  "./Model/Goal/Goal2x2x3_1x1x2.cpp"
  "./Model/Goal/Orient2x2x3_1x1x2.cpp"
  "./Model/Goal/Goal2x2x3_1x2x2.cpp"
  "./Model/Goal/Orient2x2x3_1x2x2.cpp"
  "./Model/Goal/Goal2x2x3_1x2x2_1x1x2.cpp"
  "./Model/Goal/Goal2x3x3.cpp"
  "./Model/Goal/Goal2x3x3_OE.cpp"
  "./Model/Goal/Goal3x3x3.cpp"
  "./Model/RubiksCubeModel.cpp"
  "./Model/WorldObject/Cubie.cpp"
  "./Model/WorldObject/RubiksCube.cpp")

# Build the RubiksCubee executable.
add_executable (rubiksCube ${SRC})

# Release build by default.
set(CMAKE_BUILD_TYPE Release)

# Link the OpenGLSeed library.
add_subdirectory(OpenGLSeed)
target_link_libraries (rubiksCube OpenGLSeed)

# TODO: Make cross platform.
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -Wall -pedantic -std=c++0x -Wno-strict-aliasing")

# The Find*.cmake files are here.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/OpenGLSeed/cmake/modules/")

# GLM.
find_package (GLM REQUIRED)
include_directories (${GLM_INCLUDE_DIRS})

# GLEW.
find_package (GLEW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})
target_link_libraries (rubiksCube ${GLEW_LIBRARIES})

# GLFW.
find_package (GLFW REQUIRED)
include_directories (${GLFW_INCLUDE_DIRS})
target_link_libraries (rubiksCube ${GLFW_LIBRARIES})

# OpenGL.
find_package(OpenGL REQUIRED)
include_directories (${OPENGL_INCLUDE_DIR})
target_link_libraries (rubiksCube ${OPENGL_gl_LIBRARY})

