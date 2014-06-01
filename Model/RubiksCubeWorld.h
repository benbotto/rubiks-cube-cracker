#ifndef _BUSYBIN_RUBIKS_CUBE_WORLD_H_
#define _BUSYBIN_RUBIKS_CUBE_WORLD_H_

#include "WorldObject/RubiksCube.h"
#include "../OpenGLSeed/Model/World.h"
#include "../OpenGLSeed/Model/Light/DistanceLight.h"
#include "../Controller/GL/Program/RubiksCubeProgram.h"
#include <glm/glm.hpp>
using glm::vec4;
using glm::vec3;
#include <memory>
using std::unique_ptr;
using std::move;

namespace busybin
{
  /**
   * Example world.
   */
  class RubiksCubeWorld : public World
  {
    DistanceLight distLight;

  public:
    RubiksCubeWorld(unique_ptr<Program> prog);
    RubiksCubeProgram& getProgram();
  };
}

#endif

