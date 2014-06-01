cmake_minimum_required (VERSION 2.6)
project (RubiksCube)

# All source files.
set (SRC
  "Model/WorldObject/Cubie.cpp"
  "Model/WorldObject/RubiksCube.cpp"
  "Model/RubiksCubeWorld.cpp"
  "Controller/RubiksCubeController.cpp"
  "Controller/GL/Program/RubiksCubeProgram.cpp"
  "Controller/Command/CubeMover.cpp"
  "rubiksCube.cpp")

# Build the RubiksCubee executable.
add_executable (rubiksCube ${SRC})

# Link the OpenGLSeed library.
add_subdirectory(OpenGLSeed)
target_link_libraries (rubiksCube OpenGLSeed)

# TODO: Make cross platform.
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -Wall -pedantic -std=c++0x -Wno-strict-aliasing")

# The Find*.cmake files are here.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/OpenGLSeed/cmake/modules/")

# GLM.
find_package (GLEW REQUIRED)
include_directories (${GLM_INCLUDE_DIRS})

# GLEW.
find_package (GLEW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})
target_link_libraries (rubiksCube ${GLEW_LIBRARIES})

# GLFW.
find_package (GLFW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})
target_link_libraries (rubiksCube ${GLFW_LIBRARIES})

# OpenGL.
find_package(OpenGL REQUIRED)
include_directories (${OPENGL_INCLUDE_DIR})
target_link_libraries (rubiksCube ${OPENGL_gl_LIBRARY})

