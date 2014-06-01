cmake_minimum_required (VERSION 2.6)
project (OpenGLSeed)

# All source files.
set (SRC
  "Util/VectorHelper.cpp"
  "Util/GLException.cpp"
  "Model/Iterator.cpp"
  "Model/Orbiter.cpp"
  "Model/Material/Material.cpp"
  "Model/Material/Gold.cpp"
  "Model/Material/Chrome.cpp"
  "Model/Material/Brass.cpp"
  "Model/Material/Pearl.cpp"
  "Model/Material/BlackPlastic.cpp"
  "Model/Material/WhitePlastic.cpp"
  "Model/Material/GrayPlastic.cpp"
  "Model/World.cpp"
  "Model/WorldObject/Cube.cpp"
  "Model/WorldObject/Torus.cpp"
  "Model/WorldObject/Sphere.cpp"
  "Model/WorldObject/Triangle.cpp"
  "Model/WorldObject/WorldObject.cpp"
  "Model/MatrixStack.cpp"
  "Model/Camera.cpp"
  "Model/Light/Light.cpp"
  "Model/Light/DistanceLight.cpp"
  "Model/Light/PositionalLight.cpp"
  "Model/Rotator.cpp"
  "View/WorldWindow.cpp"
  "Controller/GL/Program/Shader.cpp"
  "Controller/GL/Program/Program.cpp"
  "Controller/GL/Program/LitProgram.cpp"
  "Controller/Command/Renderer.cpp"
  "Controller/Command/Command.cpp"
  "Controller/Command/Mover.cpp"
  "Controller/Command/ViewManager.cpp"
  "Controller/Command/Looker.cpp")

# Build the OpenGLSeed library (libOpenGLSeed.a on a nix platform).
add_library(OpenGLSeed ${SRC})

# TODO: Make cross platform.
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -Wall -pedantic -std=c++0x -Wno-strict-aliasing")

# The Find*.cmake file are here.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/")

# GLM.
find_package (GLM REQUIRED)
include_directories (${GLM_INCLUDE_DIRS})

# GLEW.
find_package (GLEW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})

# GLFW.
find_package (GLFW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})

# OpenGL.
find_package(OpenGL REQUIRED)

